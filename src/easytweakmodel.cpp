#include <QDebug>
#include <QMailAccount>
#include <QMailAccountId>
#include "accountsettingsreader.h"
#include "easytweakmodel.h"

EasyTweakModel::EasyTweakModel(QObject *parent)
    : QAbstractItemModel(parent),
      mSettingsReader(new AccountSettingsReader(this))
{
    QHash<int, QByteArray> roles;
    roles[title] = "title";
    roles[tweakType] = "tweakType";
    roles[settingType] = "settingType";
    roles[settingValue] = "settingValue";
    roles[accountIdRole] = "accountIdRole";
    setRoleNames(roles);
}

void EasyTweakModel::setAccountId(const int accountId)
{
    mAccountId = accountId;
    initModel();
}

void EasyTweakModel::initModel()
{
    QMailAccountId accountId(mAccountId);
    mSettings.clear();
    if (accountId.isValid())
    {
        if (mSettingsReader->isMfeAccount(mAccountId))
        {
            EasyTweakSetting* setting = new EasyTweakSetting(QString("Sync back all Emails"),
                                                             QString("email/past_time"),
                                                             EasyTweakSetting::booleanSetting,
                                                             EasyTweakSetting::syncBack);
            mSettings.insert(EasyTweakSetting::syncBack,
                             setting);

            setting = new EasyTweakSetting(QString("Fetch full message's MIME"),
                                           QString("email/email_mime"),
                                           EasyTweakSetting::booleanSetting,
                                           EasyTweakSetting::mime);
            mSettings.insert(EasyTweakSetting::mime,
                             setting);
        }
        //TODO: find some tweaks for non-MfE accounts
    }
    reset();
}

QVariant EasyTweakModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    EasyTweakSetting* setting = getSettingFromIndex(index);
    if (!setting)
        return QVariant();

    // Some items can be processed without loading the message data
    switch(role)
    {
    case title:
        return setting->getSettingName();
    case tweakType:
        return setting->getSettingType();
    case settingType:
        return setting->getSetting();
    case settingValue:
        {
            //TODO: move all settings reader calls in EasyTweakSetting
            QVariant value = mSettingsReader->getAccountsValue(setting->getSettingKeyName(), mAccountId);
            switch(setting->getSetting())
            {
                case EasyTweakSetting::syncBack:
                    return value.toInt() ? false : true;
                case EasyTweakSetting::mime:
                    return value;
            }
        }
    case accountIdRole:
        return mAccountId;
    default:
        break;
    }

    return QVariant();
}

void EasyTweakModel::saveBoolSetting(const int index, const bool checked)
{
    if ( (index >= 0) && (index < mSettings.count()) )
    {
        const EasyTweakSetting* setting = mSettings.value(index);
        switch(setting->getSetting())
        {
        case EasyTweakSetting::syncBack:
            {
                mSettingsReader->saveAccountsSetting(mAccountId,
                                                     QString("email/past_time"),
                                                     checked ? 0 : 3);
            }
        case EasyTweakSetting::mime:
            {
            mSettingsReader->saveAccountsSetting(mAccountId,
                                                 QString("email/email_mime"),
                                                 checked ? true : false);
            mSettingsReader->saveAccountsSetting(mAccountId,
                                                 QString("email_mime"),
                                                 checked ? true : false);
            }
        }
    }
}

QModelIndex EasyTweakModel::index(int row, int column, const QModelIndex & parent) const
{
    return ((row >= 0 && column >= 0) && row < rowCount(parent)) ? createIndex(row, column, parent.row()) : QModelIndex();
}

 int EasyTweakModel::rowCount ( const QModelIndex & parent) const
 {
     Q_UNUSED(parent);
     return mSettings.count();
 }

 int EasyTweakModel::columnCount ( const QModelIndex & parent) const
 {
     Q_UNUSED(parent);
     return 1;
 }

 QModelIndex EasyTweakModel::parent(const QModelIndex &idx) const
 {
     Q_UNUSED(idx);
     return QModelIndex();
 }


EasyTweakSetting* EasyTweakModel::getSettingFromIndex(const QModelIndex& index) const
{
    if (index.isValid()) {
        int row = index.row();
        if ( (row >= 0) && (row < mSettings.count()) ) {
            return mSettings.value(row);
        }
    }

    return 0;
}
