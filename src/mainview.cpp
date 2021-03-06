#include <QDebug>
#include <QDeclarativeContext>

#include "accountslistmodel.h"
#include "easytweakmodel.h"
#include "settingslistmodel.h"
#include "foldersmodel.h"
#include "mainview.h"

static const QString defaultQmlPath = "/opt/memailsettings/memailsettings.qml";

MainView::MainView(QDeclarativeView* view, QObject *parent) :
    QObject(parent)
{
    if (view == NULL) {
        qCritical() << Q_FUNC_INFO << "view == null";
    }
    mView = view;
    mAccountsModel = new AccountsListModel(this);
    mEasyTweakModel = new EasyTweakModel(this);
    mSettingsModel = new SettingsListModel(this);
    mFoldersModel = new FoldersModel(this);
    mAccountsFoldersModel = new AccountsFoldersModel(this);

    mView->setSource(QUrl::fromLocalFile(getSourcePath()));

    QDeclarativeContext *ctxt = mView->rootContext();
    ctxt->setContextProperty("accountsModel", mAccountsModel);
    ctxt->setContextProperty("easyTweakModel", mEasyTweakModel);
    ctxt->setContextProperty("settingsModel", mSettingsModel);
    ctxt->setContextProperty("foldersModel", mFoldersModel);
    ctxt->setContextProperty("accountsFoldersModel", mAccountsFoldersModel);
}

QString MainView::getSourcePath() const
{
    return defaultQmlPath;
}

void MainView::showFullScreen()
{
    mView->showFullScreen();
}
