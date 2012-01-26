#include "accountsettingsreader.h"

// Accounts
#include <Accounts/Manager>
#include <Accounts/Service>


AccountSettingsReader::AccountSettingsReader(QObject *parent)
    : QObject(parent),
      mAccountsManager(new Accounts::Manager())
{
}
