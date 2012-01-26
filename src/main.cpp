#include <QtGui/QApplication>
#include "mainview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainView* view = new MainView();

    view->setSource(QUrl::fromLocalFile(view->getSourcePath()));
    view->showFullScreen();

    return app.exec();
}
