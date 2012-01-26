#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QDeclarativeView>

class QSettings;

class MainView : public QDeclarativeView
{
    Q_OBJECT
public:
    explicit MainView(QDeclarativeView *parent = 0);

    QString getSourcePath() const;

signals:

public slots:

private:
    QSettings* createSettings();

private:
    QSettings* mSettings;
};

#endif // MAINVIEW_H
