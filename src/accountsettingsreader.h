#ifndef ACCOUNTSETTINGSREADER_H
#define ACCOUNTSETTINGSREADER_H

#include <QObject>

// Accounts
#include <Accounts/Manager>
#include <Accounts/Provider>
#include <Accounts/Service>

class AccountSettingsReader : public QObject
{
    Q_OBJECT
public:
    explicit AccountSettingsReader(QObject *parent = 0);

   const Accounts::AccountIdList getAccountsIds() const;
   const QStringList getAccountsKeys(const Accounts::Service* service,
                                     const Accounts::AccountId& id) const;
   const QString getAccountsDisplayName(const Accounts::AccountId& id) const;
   const QString getProviderIconName(const Accounts::AccountId& id) const;
   const QVariant getAccountsValue(const Accounts::Service* service,
                                   const QString& key,
                                   const Accounts::AccountId& id) const;
   const Accounts::ServiceList getAccountsServices(const Accounts::AccountId& id) const;

private:
    Accounts::Manager* mAccountsManager;
};

#endif // ACCOUNTSETTINGSREADER_H
