#ifndef FOLDERSMODEL_H
#define FOLDERSMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QStringList>

//QMF
#include <QMailFolder>

class FolderItem : public QObject
{
    Q_OBJECT
public:
    explicit FolderItem(const QMailFolder::StandardFolder& standardFolder, const QMailFolder& mailFolder, QObject *parent = 0);

    QString getDisplayName() const;
    QString getStandardFolderName() const { return mStandardFolderName; }

private:
    void initItem();

private:
    QMailFolder::StandardFolder mStandardFolder;
    QMailFolder mFolder;
    QString mStandardFolderName;
};

//----------------------------------------------------------------------------------------------------------
// class FoldersModel

class FoldersModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Roles
    {
        standardNameRole = Qt::UserRole + 1,
        bindedFolderNameRole,
        standardFolderRole
    };

    explicit FoldersModel(QObject *parent = 0);

    Q_INVOKABLE void setAccountId(const int accountId);

    Q_INVOKABLE QString getStandardFolderName(const int folder);

    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual int rowCount (const QModelIndex & parent = QModelIndex()) const;
    virtual int	columnCount (const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &idx) const;
    virtual QVariant data(const QModelIndex& index, int role) const;


private:
    void initModel();
    int getStandardFolderByIndex(const QModelIndex& index) const;

private:
    int mAccountId;
    QList<QMailFolder::StandardFolder> mStandardFoldersEnum;
    QHash<QMailFolder::StandardFolder, FolderItem*> mStandardFolders;
};

//----------------------------------------------------------------------------------------------------------
// class AccountsFoldersModel

class AccountsFoldersModel: public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count) // Hack: we need this to make SelectionDialog happy
public:
    enum Roles
    {
        folderDisplayNameRole = Qt::UserRole + 1
    };

    explicit AccountsFoldersModel(QObject *parent = 0);

    Q_INVOKABLE void setAccountId(const int accountId);
    Q_INVOKABLE int count() { return rowCount(); }

    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual int rowCount (const QModelIndex & parent = QModelIndex()) const;
    virtual int	columnCount (const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &idx) const;
    virtual QVariant data(const QModelIndex& index, int role) const;


private:
    void initModel();
    QMailFolderId getIdFromIndex(const QModelIndex& index) const;

private:
    int mAccountId;
    QMailFolderIdList mFolders;
};

#endif // FOLDERSMODEL_H
