#ifndef SETTINGSLISTMODEL_H
#define SETTINGSLISTMODEL_H

#include <QAbstractItemModel>
#include <QMap>
#include <QStringList>

class AccountSettingsReader;

class SettingsItem: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString groupRole READ groupRole WRITE setGroupRole NOTIFY groupRoleChanged)
    Q_PROPERTY(QString keyRole READ keyRole WRITE setKeyRole NOTIFY keyRoleChanged)
    Q_PROPERTY(QString valueRole READ valueRole WRITE setValueRole NOTIFY valueRoleChanged)

public:
    SettingsItem(const QString& key, const QString& value, QObject* parent = 0);

    QString groupRole() const { return mGroup; }
    QString keyRole() const { return mKey; }
    QString valueRole() const { return mValue; }

    void setGroupRole(const QString& group)
    {
        mGroup = group;
        emit groupRoleChanged(mGroup);
    }
    void setKeyRole(const QString& key)
    {
        mKey = key;
        emit keyRoleChanged(mKey);
    }

    // returns true if value was changed
    bool setValueRole(const QString& value)
    {
        if (value != mValue)
        {
            mValue = value;
            emit valueRoleChanged(mValue);
            return true;
        }
        return false;
    }

signals:
    void valueRoleChanged(const QString value);
    void keyRoleChanged(const QString key);
    void groupRoleChanged(const QString group);

private:
    QString mGroup;
    QString mKey;
    QString mValue;
};

class SettingsListModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount)
public:

    enum Roles
    {
        keyRole = Qt::UserRole + 1,
        valueRole,
        groupRole
    };

    explicit SettingsListModel(QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE virtual int rowCount (const QModelIndex & parent = QModelIndex()) const;
    virtual int	columnCount (const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &idx) const;
    virtual QVariant data(const QModelIndex& index, int role) const;

    Q_INVOKABLE SettingsItem* get(int index) const;

    Q_INVOKABLE QString getGroup(const int index) const;
    Q_INVOKABLE void saveAccountSettings();

signals:
    void saveInProgress(bool value);
    void saveSettings(const int &id, const QStringList &keys, const QVariantList &values);

public slots:
    void setAccountId(const int id);
    void valueChanged(const QString& key, const QString& value);

private:
    QString getIdFromIndex(const QModelIndex& index) const;
    void initModel();

private slots:
    void onSaveSettings();

private:
    int mAccountId;
    QStringList mKeys;
    QStringList mChangedKeys; // FIXME: Remove this dummy member
    AccountSettingsReader* mSettingsReader;
    QMap<QString, SettingsItem*> mItemsCache;
    QStringList mGroups;
};

#endif // SETTINGSLISTMODEL_H
