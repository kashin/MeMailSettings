#include <QDebug>
#include <QSettings>
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
    roles[settingStringValue] = "settingStringValue";
    roles[accountIdRole] = "accountIdRole";
    roles[settingWarningStringValue] = "settingWarningStringValue";
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
            mSettings.append(setting);

            setting = new EasyTweakSetting(QString("Fetch full message's MIME"),
                                           QString("email_mime"),
                                           EasyTweakSetting::booleanSetting,
                                           EasyTweakSetting::mime);
            mSettings.append(setting);
            setting = new EasyTweakSetting(QString("Force EAS protocol version"),
                                           QString("use_version"),
                                           EasyTweakSetting::enumSetting,
                                           EasyTweakSetting::useVersion);
            mSettings.append(setting);
        }
        EasyTweakSetting* setting = new EasyTweakSetting(QString("Max Attachment Size"),
                                       QString(""),
                                       EasyTweakSetting::intWithWarningSetting,
                                       EasyTweakSetting::attachmentSize);
        mSettings.append(setting);
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
            if (setting->getSetting() == EasyTweakSetting::attachmentSize) {
                QSettings emailSettings("Nokia", "Fenix");
                QVariant value = emailSettings.value("maxAttachmentSize");
                return !value.isNull();
            }
            //TODO: move all settings reader calls in EasyTweakSetting
            QVariant value = mSettingsReader->getAccountsValue(setting->getSettingKeyName(), mAccountId);
            switch(setting->getSetting())
            {
                case EasyTweakSetting::syncBack:
                    return value.toInt() ? false : true;
                case EasyTweakSetting::mime:
                    return value;
                case EasyTweakSetting::useVersion:
                    return !value.isNull();
                default:
                    qWarning("oops, EasyTweakModel::data: case settingValue:");
                    return QVariant();
            }
        }
    case settingStringValue:
        {
            if (setting->getSetting() == EasyTweakSetting::attachmentSize) {
                QSettings emailSettings("Nokia", "Fenix");
                QVariant value = emailSettings.value("maxAttachmentSize");
                return value.isNull() ? QString("") : value;
            }
            QVariant value = mSettingsReader->getAccountsValue(setting->getSettingKeyName(), mAccountId);
            switch(setting->getSetting())
            {
                case EasyTweakSetting::syncBack:
                case EasyTweakSetting::mime:
                    return QString("");
                case EasyTweakSetting::useVersion:
                    return value.isValid() ? value : QString("");
                default:
                    return QVariant();
            }
        }
    case accountIdRole:
        return mAccountId;
    case settingWarningStringValue:
        // yes, I know, hardcoded text is a dump idea, but I do believe that this is going to be a last
        // update for this application, so who cares how it is implemented? :)
        return QString("Warning. Too large attachment \n might be not supported \n by your email server");
    default:
        qWarning() << "unhandled role!";
        break;
    }

    return QVariant();
}

void EasyTweakModel::saveBoolSetting(const int index, const bool checked)
{
    if ( (index >= 0) && (index < mSettings.count()) )
    {
        const EasyTweakSetting* setting = mSettings.at(index);
        switch(setting->getSetting())
        {
        case EasyTweakSetting::syncBack:
            {
                mSettingsReader->saveAccountsSetting(mAccountId,
                                                     setting->getSettingKeyName(),
                                                     checked ? 0 : 3);
                break;
            }
        case EasyTweakSetting::mime:
            {
                mSettingsReader->saveAccountsSetting(mAccountId,
                                                 setting->getSettingKeyName(),
                                                 checked ? true : false);
                mSettingsReader->saveAccountsSetting(mAccountId, QString("email/") +
                                                 setting->getSettingKeyName(),
                                                 checked ? true : false);
                break;
            }
        default:
            break;
        }
    }
}

void EasyTweakModel::saveEnumSetting(const int index, const bool checked, const QVariant &value)
{
    if ( (index >= 0) && (index < mSettings.count()) )
    {
        const EasyTweakSetting* setting = mSettings.at(index);
        switch(setting->getSetting())
        {
            case EasyTweakSetting::useVersion:
                {
                    if (checked)
                    {
                        mSettingsReader->saveAccountsSetting(mAccountId,
                                             setting->getSettingKeyName(),
                                                         value);
                    }
                    else
                    {
                        mSettingsReader->removeEmailSetting(mAccountId,
                                             setting->getSettingKeyName());
                    }
                }
            case EasyTweakSetting::syncBack:
            case EasyTweakSetting::mime:
                return;
            default:
                qDebug() << Q_FUNC_INFO << "wtf???";
                return;
        }
    }
}

void EasyTweakModel::saveStringSetting(const int index, const bool checked,const QVariant &value)
{
    if ( (index >= 0) && (index < mSettings.count()) )
    {
        const EasyTweakSetting* setting = mSettings.at(index);
        switch(setting->getSetting())
        {
            case EasyTweakSetting::useVersion:
                {
                    if (checked)
                    {
                        mSettingsReader->saveAccountsSetting(mAccountId,
                                             setting->getSettingKeyName(),
                                                         value);
                    }
                    else
                    {
                        mSettingsReader->removeEmailSetting(mAccountId,
                                             setting->getSettingKeyName());
                    }
                }
            case EasyTweakSetting::syncBack:
            case EasyTweakSetting::mime:
                return;
            default:
                qDebug() << Q_FUNC_INFO << "wtf???";
                return;
        }
    }
}

void EasyTweakModel::saveIntWithWarningSetting(const int index, const bool checked, const QVariant &value)
{
    if ( (index >= 0) && (index < mSettings.count()) )
    {
        const EasyTweakSetting* setting = mSettings.at(index);
        if (setting->getSetting() == EasyTweakSetting::attachmentSize)
        {
            QSettings emailSettings("Nokia", "Fenix");
            if (checked) {
                emailSettings.setValue("maxAttachmentSize", value);
            } else {
                emailSettings.remove("maxAttachmentSize");
            }
            emailSettings.sync();
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
