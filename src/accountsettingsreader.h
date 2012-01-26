#ifndef ACCOUNTSETTINGSREADER_H
#define ACCOUNTSETTINGSREADER_H

#include <QObject>

namespace Accounts{
    class Manager;
}

class AccountSettingsReader : public QObject
{
    Q_OBJECT
public:
    explicit AccountSettingsReader(QObject *parent = 0);

signals:

public slots:

private:
    Accounts::Manager* mAccountsManager;
};

#endif // ACCOUNTSETTINGSREADER_H
