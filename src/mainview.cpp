#include <QSettings>
#include <QDebug>
#include <QDeclarativeContext>

#include "accountslistmodel.h"
#include "mainview.h"

static const char* organization = "MeMailSettings";
static const char* application = "memailsettings";
static const char* defaultQmlPath = "/opt/MeMailSettings/qml/main.qml";

MainView::MainView(QDeclarativeView *parent) :
    QDeclarativeView(parent)
{
    mSettings = createSettings();
    mAccountsModel = new AccountsListModel(this);

    QDeclarativeContext *ctxt = rootContext();
    ctxt->setContextProperty("accountsModel", mAccountsModel);
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
