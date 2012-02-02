#ifndef ACCOUNTSLISTMODEL_H
#define ACCOUNTSLISTMODEL_H

#include "accountsettingsreader.h"

#include <QAbstractItemModel>

class AccountSettingsReader;

class AccountsListModel: public QAbstractItemModel
{
Q_OBJECT
public:
    enum Roles
    {
        iconSource = Qt::UserRole + 1,
        title,
        subtitle,
        accountIdRole
    };

    AccountsListModel(QObject* parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual int	rowCount (const QModelIndex & parent = QModelIndex()) const;
    virtual int	columnCount (const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &idx) const;
    virtual QVariant data(const QModelIndex& index, int role) const;

private:
    Accounts::AccountId getIdFromIndex(const QModelIndex& index) const;

private:
    AccountSettingsReader* mAccountSettingsReader;
    Accounts::AccountIdList mIds;
};

#endif // ACCOUNTSLISTMODEL_H
