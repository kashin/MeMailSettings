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

class FoldersModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Roles
    {
        standardNameRole = Qt::UserRole + 1,
        bindedFolderNameRole
    };

    explicit FoldersModel(QObject *parent = 0);

    Q_INVOKABLE void setAccountId(const int accountId);

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

#endif // FOLDERSMODEL_H
