#include "accountsettingsreader.h"

//Qt
#include <QDebug>
#include <QVariant>
#include <QTimer>

using namespace Accounts;

AccountSettingsReader::AccountSettingsReader(QObject *parent)
    : QObject(parent),
      mAccountsManager(new Manager("e-mail"))
{
}

const AccountIdList AccountSettingsReader::getAccountsIds(const QString providerName) const
{
    if (mAccountsManager)
    {
        if (providerName.isEmpty())
        {
            return mAccountsManager->accountListEnabled("e-mail");
        }
        AccountIdList ids = mAccountsManager->accountListEnabled("e-mail");
        AccountIdList resIds;
        foreach(AccountId id, ids)
        {
            qDebug() << Q_FUNC_INFO << "Account=" << id;
            if (getProviderName(id) == providerName)
            {
                qDebug() << Q_FUNC_INFO << "Account" << id << "is" << providerName << "account";
                resIds << id;
            }
        }
        return resIds;
    }
    qCritical() << Q_FUNC_INFO << "something nasty is happened, accounts manager is NULL!";
    return AccountIdList();
}

const QStringList AccountSettingsReader::getAccountsKeys(const Service* service,
                                                         const AccountId& id) const
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        acc->selectService(service);
        qCritical() << Q_FUNC_INFO << acc->allKeys(); //remove it after debug
        return acc->allKeys();
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return QStringList();
}

const QString AccountSettingsReader::getAccountsDisplayName(const AccountId &id) const
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        return acc->displayName();
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return QString();
}

const QString AccountSettingsReader::getProviderIconName(const AccountId& id) const
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        Provider *provider = mAccountsManager->provider(acc->providerName());
        if(!provider)
        {
            qWarning() << Q_FUNC_INFO << "there is no such provider:" << acc->providerName();
            return QString();
        }

        return provider->iconName();
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return QString();
}

const QString AccountSettingsReader::getProviderName(const AccountId& id) const
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        Provider *provider = mAccountsManager->provider(acc->providerName());
        if(!provider)
        {
            qWarning() << Q_FUNC_INFO << "there is no such provider:" << acc->providerName();
            return QString();
        }

        return provider->name();
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return QString();
}

const QVariant AccountSettingsReader::getAccountsValue(const QString& key,
                                const AccountId& id) const
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        QVariant result;

        Accounts::ServiceList services = acc->services();
        services.append((Accounts::Service*)NULL);

        foreach (const Accounts::Service* service, services)
        {
            acc->selectService(service);
            Accounts::SettingSource source;
            result = acc->valueAsString(key, QString(), &source);
            if (source != Accounts::NONE)
            {
                delete acc;
                return result;
            }
            //argh, useless crap is bellow
            result = acc->valueAsInt(key, -1, &source);
            if (source != Accounts::NONE)
            {
                delete acc;
                return result;
            }
            result = acc->valueAsBool(key, false, &source);
            if (source != Accounts::NONE)
            {
                delete acc;
                return result;
            }
            // end of useles crap
        }
        qWarning() << Q_FUNC_INFO << "something is wrong! Value for key:" << key << "is not found";
        delete acc;
        return QVariant();
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return QVariant();
}

const Accounts::ServiceList AccountSettingsReader::getAccountsServices(const Accounts::AccountId &id) const
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        Accounts::ServiceList services = acc->services();
        services.append((Accounts::Service*)NULL);
        qDebug() << Q_FUNC_INFO << services.count();
        delete acc;
        return services;
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return Accounts::ServiceList();
}

void AccountSettingsReader::saveAccountsSetting(const Accounts::AccountId &id, const QString &key, const QVariant &value)
{
    // TODO: add Service for EasyTweak Mode

    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        Accounts::ServiceList services = acc->services();
        services.append((Accounts::Service*)NULL);
        // yeah, I know it looks nasty but since I din't mapped
        // keys and services yet...
        foreach (const Accounts::Service* service, services)
        {
            acc->selectService(service);
            Accounts::SettingSource source;
            acc->valueAsString(key, QString(), &source);
            if (source != Accounts::NONE)
            {
                if ((QString::compare(value.toString(), QString("true"), Qt::CaseInsensitive) == 0) ||
                    (QString::compare(value.toString(), QString("false"), Qt::CaseInsensitive) == 0))
                    acc->setValue(key, value.toBool());
                else
                    acc->setValue(key, value);
                acc->syncAndBlock();
                delete acc;
                return;
            }
        }
        // Saving a new setting in the account as an Email setting
        qDebug() << Q_FUNC_INFO << "saving a new setting as an email setting. Key=" << key
                 << "value=" << value;
        Accounts::Service* mfeMailService = 0;
        foreach (Accounts::Service* service, services)
        {
            if (service && service->serviceType() == "e-mail")
            {
                mfeMailService = service;
                break;
            }
        }

        if (mfeMailService == 0)
            qWarning() << Q_FUNC_INFO << "Mail service is 0!";
        acc->selectService(mfeMailService);
        acc->setValue(key, value);
        acc->syncAndBlock();
        delete acc;
        return;
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return;
}

void AccountSettingsReader::removeGlobalSetting(const Accounts::AccountId &id, const QString &key)
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        acc->selectService(NULL);
        acc->remove(key);
        acc->syncAndBlock();
        delete acc;
        return;
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return;
}

void AccountSettingsReader::removeEmailSetting(const Accounts::AccountId &id, const QString &key)
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        Accounts::ServiceList services = acc->services();
        Accounts::Service* mfeMailService = 0;
        foreach (Accounts::Service* service, services)
        {
            if (service && service->serviceType() == "e-mail")
            {
                mfeMailService = service;
                break;
            }
        }
        if (mfeMailService == 0)
            qWarning() << Q_FUNC_INFO << "Mail service is 0!";

        acc->selectService(mfeMailService);
        acc->remove(key);
        acc->syncAndBlock();
        delete acc;
        return;
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return;
}

bool AccountSettingsReader::isMfeAccount(const Accounts::AccountId &id)
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        if (acc->providerName() == QString("mfe"))
        {
            qDebug() << "Account" << id << "is an MfE account.";
            return true;
        }
        else
        {
            qDebug() << "Account" << id << "is not an MfE account.";
            return false;
        }
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return false;
}

void AccountSettingsReader::onSaveAccountSettings(const int &id,
                                                  const QStringList &keys,
                                                  QVariantList values)
{
    foreach (const QString& key, keys)
    {
        if (!values.isEmpty())
            saveAccountsSetting(id, key, values.takeFirst());
        else
        {
            qCritical() << Q_FUNC_INFO << "Ouch, something nasty is happened. Keys list is bigger then values list!";
            return;
        }
    }
    //FIXME: stupid workaround to show progress dialog if we are saving too few settings
    QTimer::singleShot(1000, this, SIGNAL(settingsSaved()));
}
