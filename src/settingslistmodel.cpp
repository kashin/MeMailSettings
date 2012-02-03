#include "settingslistmodel.h"
#include "accountsettingsreader.h"

#include <QStringList>
#include <QDebug>
#include <QTimer>

bool lessThen(const QString& first, const QString& second)
{
    const int firstSeparatorIndex = first.indexOf("/");
    const int secondSeparatorIndex = second.indexOf("/");
    if ( (firstSeparatorIndex == -1) &&
         (secondSeparatorIndex != -1))
    {
        return true;
    }
    if ( (firstSeparatorIndex != -1) &&
         (secondSeparatorIndex == -1))
    {
        return false;
    }
    return first < second;
}

SettingsItem::SettingsItem(const QString &key, const QString &value, QObject *parent)
    : QObject(parent),
      mKey(key),
      mValue(value)
{
    const int separatorIndex = mKey.indexOf("/");
    if (separatorIndex == -1) // slash is not found, so it is a global setting
    {
        mGroup = "Global";
    }
    else
    {
        mGroup = mKey.left(separatorIndex);
    }
}


SettingsListModel::SettingsListModel(QObject *parent)
    : QAbstractItemModel(parent),
      mAccountId(0),
      mSettingsReader(new AccountSettingsReader(this))
{
    connect(mSettingsReader, SIGNAL(settingsSaved()), this, SLOT(onSaveSettings()));
    connect(this, SIGNAL(saveSettings(int,QStringList,QVariantList)),
            mSettingsReader, SLOT(onSaveAccountSettings(int,QStringList,QVariantList)));
    QHash<int, QByteArray> roles;
    roles[keyRole] = "keyRole";
    roles[valueRole] = "valueRole";
    roles[groupRole] = "groupRole";
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

void SettingsListModel::saveAccountSettings()
{
    emit saveInProgress(true);
    QVariantList values;
    foreach (const QString& key, mChangedKeys)
    {
        if (mItemsCache.contains(key))
        {
            values.append(mItemsCache.value(key)->valueRole());
        }
        else
        {
            qCritical() << Q_FUNC_INFO << "There is no" << key << "setting in the account" << mAccountId;
        }
    }
    emit saveSettings(mAccountId, mChangedKeys, values);
}

void SettingsListModel::valueChanged(const QString &key, const QString &value)
{
    if (!mItemsCache.contains(key))
    {
        qCritical() << Q_FUNC_INFO << "Thereis no " << key << "in the items cache!";
        return;
    }
    mItemsCache.value(key)->setValueRole(value);
    if (!mChangedKeys.contains(key))
        mChangedKeys.append(key);
}

void SettingsListModel::initModel()
{
    mKeys = QStringList();
    mItemsCache.clear();
    mGroups.clear();

    foreach (const Accounts::Service* service, mSettingsReader->getAccountsServices(mAccountId))
    {
        mKeys += mSettingsReader->getAccountsKeys(service, mAccountId);
    }

    qSort(mKeys.begin(), mKeys.end(), lessThen);

    foreach(const QString& key, mKeys)
    {
        SettingsItem* item = new SettingsItem(key,
                                              mSettingsReader->getAccountsValue(key,mAccountId).toString()
                                              ,this);
        mItemsCache.insert(key, item);
        if (!mGroups.contains(item->groupRole()))
            mGroups.append(item->groupRole());
    }

    reset();
}

void SettingsListModel::onSaveSettings()
{
    mChangedKeys.clear();
    emit saveInProgress(false);
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

    switch(role)
    {
    case keyRole:
        return key;

    case valueRole:
    {
        if (mItemsCache.contains(key))
        {
            const SettingsItem* item = mItemsCache.value(key);
            return item->valueRole();
        }
        else
        {
            qWarning() << Q_FUNC_INFO << "There is no" << key << "setting";
            break;
        }
    }
    case groupRole:
    {
        if (mItemsCache.contains(key))
        {
            const SettingsItem* item = mItemsCache.value(key);
            return item->groupRole();
        }
        else
        {
            qWarning() << Q_FUNC_INFO << "There is no" << key << "setting";
            break;
        }
    }

    default:
        break;
    }

    return QVariant();
}

SettingsItem* SettingsListModel::get(int index) const
{
    if (index < mKeys.count() && index >=0 && mItemsCache.contains(mKeys.at(index)))
        return mItemsCache.value(mKeys.at(index));
    qWarning() << Q_FUNC_INFO << "There is no " << index << " index!";
    return 0;
}


QString SettingsListModel::getGroup(const int index) const
{
    if (index >= 0 && index < mGroups.count())
        return mGroups.at(index);
    qWarning() << Q_FUNC_INFO << "there is no" << index << "index!";
    return QString();
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
