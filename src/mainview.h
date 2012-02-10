#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QDeclarativeView>

class QSettings;
class AccountsListModel;
class SettingsListModel;
class FoldersModel;
class AccountsFoldersModel;

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
    AccountsListModel* mAccountsModel;
    SettingsListModel* mSettingsModel;
    FoldersModel* mFoldersModel;
    AccountsFoldersModel* mAccountsFoldersModel;
};

#endif // MAINVIEW_H
