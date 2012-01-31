#include "settingslistmodel.h"
#include "accountsettingsreader.h"

#include <QStringList>
#include <QDebug>

SettingsListModel::SettingsListModel(QObject *parent)
    : QAbstractItemModel(parent),
      mAccountId(0),
      mSettingsReader(new AccountSettingsReader(this))
{
    QHash<int, QByteArray> roles;
    roles[keyRole] = "keyRole";
    roles[valueRole] = "valueRole";
    setRoleNames(roles);
}

QModelIndex SettingsListModel::index(int row, int column, const QModelIndex & parent) const
{
    return ((row >= 0 && column >= 0) && row < rowCount(parent)) ? createIndex(row, column, parent.row()) : QModelIndex();
}

void SettingsListModel::setAccountId(const int id)
{
    mAccountId = id;
    initModel();
}

void SettingsListModel::initModel()
{
    mKeys = QStringList();
    foreach (const Accounts::Service* service, mSettingsReader->getAccountsServices(mAccountId))
    {
        mKeys += mSettingsReader->getAccountsKeys(service, mAccountId);
    }
    qDebug() << Q_FUNC_INFO << mKeys.count();
    reset();
}

int SettingsListModel::rowCount ( const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return mKeys.count();
}

int SettingsListModel::columnCount ( const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QModelIndex SettingsListModel::parent(const QModelIndex &idx) const
{
    Q_UNUSED(idx);
    return QModelIndex();
}

QVariant SettingsListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QString key = getIdFromIndex(index);
    if (key.isEmpty())
        return QVariant();

    // Some items can be processed without loading the message data
    switch(role)
    {
    case keyRole:
        return key;

    case valueRole:
    {
        QVariant result;
        result = mSettingsReader->getAccountsValue(key, mAccountId);
        qDebug() << Q_FUNC_INFO << "value=" << result;
        return result;
    }

    default:
        break;
    }

    return QVariant();
}

QString SettingsListModel::getIdFromIndex(const QModelIndex& index) const
{
    if (index.isValid()) {
        int row = index.row();
        if ((row >= 0) && (row < mKeys.count())) {
            qDebug() << Q_FUNC_INFO << mKeys.at(row);
            return mKeys.at(row);
        }
    }

    return QString();
}
