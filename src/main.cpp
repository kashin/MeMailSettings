#include <QDeclarativeComponent>
#include <QDeclarativeView>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QMailStore>
#include <QApplication>
#include <MDeclarativeCache>
#include "mainview.h"

static QApplication *app;

static QDeclarativeView *declView;

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    app = MDeclarativeCache::qApplication(argc, argv);

    declView = MDeclarativeCache::qDeclarativeView();
    declView->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    Q_ASSERT(QMailStore::instance()); // Let's init Mail Store here.

    MainView mainView(declView);

    mainView.showFullScreen();

    return app->exec();
}
