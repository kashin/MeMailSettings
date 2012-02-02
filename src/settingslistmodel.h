#ifndef SETTINGSLISTMODEL_H
#define SETTINGSLISTMODEL_H

#include <QAbstractItemModel>
#include <QMap>
#include <QStringList>

class AccountSettingsReader;

class SettingsListModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    enum Roles
    {
        keyRole = Qt::UserRole + 1,
        valueRole
    };

    explicit SettingsListModel(QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual int	rowCount (const QModelIndex & parent = QModelIndex()) const;
    virtual int	columnCount (const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &idx) const;
    virtual QVariant data(const QModelIndex& index, int role) const;

signals:
    void saveInProgress();

public slots:
    void setAccountId(const int id);
    void saveAccountSetting(const QString& key, const QVariant& value);

private:
    QString getIdFromIndex(const QModelIndex& index) const;
    void initModel();

private:
    int mAccountId;
    QStringList mKeys;
    AccountSettingsReader* mSettingsReader;
};

#endif // SETTINGSLISTMODEL_H
