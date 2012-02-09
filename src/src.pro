TEMPLATE = app
QT += core gui declarative
TARGET = memailsettings

target.path = $$INSTALL_ROOT/bin

INSTALLS += target

CONFIG += link_pkgconfig
PKGCONFIG += qmfclient accounts-qt aegis-certman

QMAKE_CXXFLAGS *= -Werror \ #yes, I don't like warnings :)

SOURCES += main.cpp \
           mainview.cpp \
           accountsettingsreader.cpp \
           accountslistmodel.cpp \
           settingslistmodel.cpp \
           foldersmodel.cpp

HEADERS += mainview.h \
           accountsettingsreader.h \
           accountslistmodel.h \
           settingslistmodel.h \
           foldersmodel.h

qml_files.files += ../qml/MeMailSettings/main.qml \
                   ../qml/MeMailSettings/AboutDialog.qml \
                   ../qml/MeMailSettings/AccountsListView.qml \
                   ../qml/MeMailSettings/AccountsItem.qml \
                   ../qml/MeMailSettings/AccountsPage.qml \
                   ../qml/MeMailSettings/FoldersItem.qml \
                   ../qml/MeMailSettings/FoldersListPage.qml \
                   ../qml/MeMailSettings/FoldersListView.qml \
                   ../qml/MeMailSettings/SettingsListPage.qml \
                   ../qml/MeMailSettings/SettingsListView.qml \
                   ../qml/MeMailSettings/SettingsItem.qml \
                   ../qml/MeMailSettings/MainMenu.qml \
                   ../qml/MeMailSettings/MainPage.qml \
                   ../qml/MeMailSettings/SettingsPageMenu.qml \
                   ../qml/MeMailSettings/SectionHeaderItem.qml

qml_files.path = $$INSTALL_QML_ROOT

INSTALLS += qml_files
