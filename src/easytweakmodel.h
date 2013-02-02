#ifndef EASYTWEAKMODEL_H
#define EASYTWEAKMODEL_H

#include <QAbstractItemModel>
#include <QHash>

class AccountSettingsReader;

class EasyTweakSetting
{
public:
    enum Types {
        booleanSetting = 0,
        enumSetting,       //for future updates for non-boolean settings
        stringSetting,       //for future updates for non-boolean settings
        intSetting           //for future updates for non-boolean settings
    };

    enum Settings {
        syncBack = 0,
        mime,
        useVersion
    };

    explicit EasyTweakSetting(const QString& settingName,
                              const QString& keyName,
                              const Types& type,
                              const Settings& set)
        : mSetting(set),
          mType(type),
          mKeyName(keyName),
          mName(settingName)
    {
    }

    const QString getSettingName() const { return mName; }
    const QString getSettingKeyName() const { return mKeyName; }
    Types getSettingType() const { return mType; }
    Settings getSetting() const { return mSetting; }

private:
    Settings mSetting;
    Types mType;
    QString mKeyName;
    QString mName;
};

class EasyTweakModel: public QAbstractItemModel
{
Q_OBJECT
public:
    enum Roles
    {
        title = Qt::UserRole + 1,
        tweakType,
        settingType,
        settingValue,
        settingStringValue,
        accountIdRole
    };

    explicit EasyTweakModel(QObject* parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual int	rowCount (const QModelIndex & parent = QModelIndex()) const;
    virtual int	columnCount (const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &idx) const;
    virtual QVariant data(const QModelIndex& index, int role) const;

    Q_INVOKABLE void setAccountId(const int accountId);
    Q_INVOKABLE void saveBoolSetting(const int index, const bool checked);
    Q_INVOKABLE void saveEnumSetting(const int index, const bool checked, const QVariant& value);
    Q_INVOKABLE void saveStringSetting(const int index, const bool checked, const QVariant& value);

private:
    EasyTweakSetting* getSettingFromIndex(const QModelIndex& index) const;
    void initModel();

private:
    int mAccountId;
    QHash<int, EasyTweakSetting*> mSettings;
    AccountSettingsReader* mSettingsReader;
};

#endif // EASYTWEAKMODEL_H
