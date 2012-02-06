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

const AccountIdList AccountSettingsReader::getAccountsIds() const
{
    if (mAccountsManager)
        return mAccountsManager->accountListEnabled("e-mail");
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
                acc->setValue(key, value);
                acc->syncAndBlock();
                delete acc;
                return;
            }
        }
        qWarning() << Q_FUNC_INFO << "Setting" << key << "is not saved in account" << id;
        delete acc;
        return;
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return;
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
