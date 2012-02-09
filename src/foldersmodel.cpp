#include "foldersmodel.h"

#include <QMailAccount>
#include <QMailStore>

FolderItem::FolderItem(const QMailFolder::StandardFolder &standardFolder, const QMailFolder &mailFolder, QObject *parent)
    : QObject(parent),
      mStandardFolder(standardFolder),
      mFolder(mailFolder)
{
    initItem();
}

void FolderItem::initItem()
{
    switch(mStandardFolder)
    {
    case QMailFolder::InboxFolder:
    {
        mStandardFolderName = QString("Inbox");
        break;
    }
    case QMailFolder::DraftsFolder:
    {
        mStandardFolderName = QString("Drafts");
        break;
    }
    case QMailFolder::TrashFolder:
    {
        mStandardFolderName = QString("Trash");
        break;
    }
    case QMailFolder::SentFolder:
    {
        mStandardFolderName = QString("Sent Items");
        break;
    }
    case QMailFolder::JunkFolder:
    {
        mStandardFolderName = QString("Junk");
        break;
    }
    default:
        break;
    }
}

QString FolderItem::getDisplayName() const
{
    return mFolder.displayName();
}

FoldersModel::FoldersModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mStandardFoldersEnum.append(QMailFolder::InboxFolder);
    mStandardFoldersEnum.append(QMailFolder::DraftsFolder);
    mStandardFoldersEnum.append(QMailFolder::SentFolder);
    mStandardFoldersEnum.append(QMailFolder::TrashFolder);
    mStandardFoldersEnum.append(QMailFolder::JunkFolder);

    QHash<int, QByteArray> roles;
    roles[standardNameRole] = "standardNameRole";
    roles[bindedFolderNameRole] = "bindedFolderNameRole";
    setRoleNames(roles);
}

void FoldersModel::initModel()
{
    mStandardFolders.clear();
    Q_ASSERT(QMailStore::instance());
    QMailAccountId accountId(mAccountId);
    if (accountId.isValid())
    {
        QMailAccount account(accountId);
        foreach (const QMailFolder::StandardFolder& stFolder, mStandardFoldersEnum)
        {
            const QMailFolderId& standardFolderId = account.standardFolder(stFolder);
            FolderItem* item = new FolderItem(stFolder, QMailFolder(standardFolderId), this);
            mStandardFolders.insert(stFolder, item);
        }
    }
}

void FoldersModel::setAccountId(const int accountId)
{
    mAccountId = accountId;
    initModel();
}

int FoldersModel::getStandardFolderByIndex(const QModelIndex& index) const
{
    int row = index.row();
    if ((row >= 0) && (row < mStandardFoldersEnum.count())) {
        return mStandardFoldersEnum.at(row);
    }
    qWarning() << Q_FUNC_INFO << "there is no " << row << "row in the folders list";
    return -1;
}

QModelIndex FoldersModel::index(int row, int column, const QModelIndex &parent) const
{
    return ((row >= 0 && column >= 0) && row < rowCount(parent))
            ? createIndex(row, column, parent.row())
            : QModelIndex();
}

int FoldersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mStandardFoldersEnum.count();
}

int FoldersModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QModelIndex FoldersModel::parent(const QModelIndex &idx) const
{
    Q_UNUSED(idx);
    return QModelIndex();
}

QVariant FoldersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int retVal = getStandardFolderByIndex(index);
    QMailFolder::StandardFolder stFolder;
    if (retVal != -1)
        stFolder = QMailFolder::StandardFolder(retVal);
    else
        return QVariant();

    switch(role)
    {
    case standardNameRole:
    {
        if (mStandardFolders.contains(stFolder))
            return mStandardFolders.value(stFolder)->getStandardFolderName();
        qCritical() << Q_FUNC_INFO << "Ouch, something nasty is happened, there is no folder" << stFolder << " in Hash";
        return QVariant();
    }
    case bindedFolderNameRole:
    {
        if (mStandardFolders.contains(stFolder))
            return mStandardFolders.value(stFolder)->getDisplayName();
        qCritical() << Q_FUNC_INFO << "Ouch, something nasty is happened, there is no folder" << stFolder << " in Hash";
        return QVariant();
    }
    default:
        break;
    }

    return QVariant();
}
