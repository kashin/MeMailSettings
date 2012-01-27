#include "accountsettingsreader.h"

//Qt
#include <QDebug>

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

const QStringList AccountSettingsReader::getAccountsKeys(const Service& service,
                                                         const AccountId& id) const
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        acc->selectService(&service);
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

const QVariant AccountSettingsReader::getAccountsValue(const Service& service,
                                const QString& key,
                                const AccountId& id) const
{
    Account *acc = mAccountsManager->account(id);
    if (acc)
    {
        QVariant result;
        acc->selectService(&service);
        acc->value(key, result);
        delete acc;
        qDebug() << Q_FUNC_INFO << "result:" << result;
        return result;
    }
    qWarning() << Q_FUNC_INFO << "account" << id << "not found";
    return QString();
}

