#include <QDebug>
#include "accountslistmodel.h"

AccountsListModel::AccountsListModel(QObject *parent)
    : QAbstractItemModel(parent),
      mAccountSettingsReader(new AccountSettingsReader(this))
{
    mIds = mAccountSettingsReader->getAccountsIds();
    qCritical() << Q_FUNC_INFO << mIds;
    QHash<int, QByteArray> roles;
    roles[iconRole] = "iconRole";
    roles[displayNameRole] = "displayNameRole";
    roles[accountIdRole] = "accountIdRole";
    setRoleNames(roles);
}

QModelIndex AccountsListModel::index(int row, int column, const QModelIndex & parent) const
{
    return ((row >= 0 && column >= 0) && row < rowCount(parent)) ? createIndex(row, column, parent.row()) : QModelIndex();
}

 int AccountsListModel::rowCount ( const QModelIndex & parent) const
 {
     Q_UNUSED(parent);
     return mIds.count();
 }

 int AccountsListModel::columnCount ( const QModelIndex & parent) const
 {
     Q_UNUSED(parent);
     return 1;
 }

 QModelIndex AccountsListModel::parent(const QModelIndex &idx) const
 {
     Q_UNUSED(idx);
     return QModelIndex();
 }

QVariant AccountsListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Accounts::AccountId id = getIdFromIndex(index);
    if (!id)
        return QVariant();

    // Some items can be processed without loading the message data
    switch(role)
    {
    case iconRole:
        return mAccountSettingsReader->getProviderIconName(id);

    case displayNameRole:
        return mAccountSettingsReader->getAccountsDisplayName(id);
    case accountIdRole:
        return id;

    default:
        break;
    }

    return QVariant();
}

Accounts::AccountId AccountsListModel::getIdFromIndex(const QModelIndex& index) const
{
    if (index.isValid()) {
        int row = index.row();
        if ((row >= 0) && (row < mIds.count())) {
            qCritical() << Q_FUNC_INFO << mIds.at(row);
            return mIds.at(row);
        }
    }

    return 0;
}
