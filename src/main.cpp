#include <QtGui/QApplication>
#include <QMailStore>
#include "mainview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainView* view = new MainView();

    Q_ASSERT(QMailStore::instance()); // Let's init Mail Store here.

    view->setSource(QUrl::fromLocalFile(view->getSourcePath()));
    view->showFullScreen();

    return app.exec();
}
