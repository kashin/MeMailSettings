#include <QSettings>
#include <QDebug>
#include <QDeclarativeContext>

#include "accountslistmodel.h"
#include "settingslistmodel.h"
#include "foldersmodel.h"
#include "mainview.h"

static const char* organization = "MeMailSettings";
static const char* application = "memailsettings";
static const char* defaultQmlPath = "/usr/share/memailsettings/memailsettings.qml";

MainView::MainView(QDeclarativeView *parent) :
    QDeclarativeView(parent)
{
    mSettings = createSettings();
    mAccountsModel = new AccountsListModel(this);
    mSettingsModel = new SettingsListModel(this);
    mFoldersModel = new FoldersModel(this);
    mAccountsFoldersModel = new AccountsFoldersModel(this);

    QDeclarativeContext *ctxt = rootContext();
    ctxt->setContextProperty("accountsModel", mAccountsModel);
    ctxt->setContextProperty("settingsModel", mSettingsModel);
    ctxt->setContextProperty("foldersModel", mFoldersModel);
    ctxt->setContextProperty("accountsFoldersModel", mAccountsFoldersModel);
}

QString MainView::getSourcePath() const
{
    return mSettings->value("Qml/Path",defaultQmlPath).toString();
}

QSettings* MainView::createSettings()
{
    QSettings* settings = new QSettings(organization, application, this);

    QStringList groups = settings->childGroups();
    if (!groups.contains("Qml"))
    {
        settings->beginGroup("Qml");
        settings->setValue("Path", defaultQmlPath);
        settings->endGroup();
    }
    settings->sync();
    //TODO: add file system watcher to track changes in conf file.
    return settings;
}
