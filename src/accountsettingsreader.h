#ifndef ACCOUNTSETTINGSREADER_H
#define ACCOUNTSETTINGSREADER_H

#include <QObject>
#include <QVariant>

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
   const QString getProviderName(const Accounts::AccountId& id) const;
   const QVariant getAccountsValue(const QString& key,
                                   const Accounts::AccountId& id) const;
   const Accounts::ServiceList getAccountsServices(const Accounts::AccountId& id) const;
   void saveAccountsSetting(const Accounts::AccountId& id,
                            const QString& key, const QVariant& value);
signals:
   void settingsSaved();

public slots:
   void onSaveAccountSettings(const int &id,
                        const QStringList &keys,
                        QVariantList values);

private:
    Accounts::Manager* mAccountsManager;
};

#endif // ACCOUNTSETTINGSREADER_H
