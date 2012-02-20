TEMPLATE = app
QT += declarative
CONFIG += meegotouch
TARGET = "memailsettings"
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += link_pkgconfig
PKGCONFIG += qmfclient accounts-qt aegis-certman

QMAKE_CXXFLAGS *= -Werror \ #yes, I don't like warnings :)

HEADERS += mainview.h \
           accountsettingsreader.h \
           accountslistmodel.h \
           settingslistmodel.h \
           foldersmodel.h

SOURCES += main.cpp \
           mainview.cpp \
           accountsettingsreader.cpp \
           accountslistmodel.cpp \
           settingslistmodel.cpp \
           foldersmodel.cpp

  unix {
    #VARIABLES
    isEmpty(PREFIX) {
        PREFIX = /usr
  }
BINDIR = $$PREFIX/bin
DATADIR =$$PREFIX/share

DEFINES += DATADIR=\\\"$$DATADIR\\\" PKGDATADIR=\\\"$$PKGDATADIR\\\"

INSTALLS += target qmlgui desktop icon80

  target.path =$$BINDIR

  qmlgui.path = $$DATADIR/$${TARGET}
  qmlgui.files += qml/memailsettings.qml \
                  qml/AboutDialog.qml \
                  qml/AccountsListHeader.qml \
                  qml/AccountsListView.qml \
                  qml/AccountsItem.qml \
                  qml/AccountsPage.qml \
                  qml/FoldersItem.qml \
                  qml/FoldersListPage.qml \
                  qml/FoldersListView.qml \
                  qml/SettingsListPage.qml \
                  qml/SettingsListView.qml \
                  qml/SettingsItem.qml \
                  qml/MainMenu.qml \
                  qml/MainPage.qml \
                  qml/SettingsPageMenu.qml \
                  qml/SectionHeaderItem.qml \
                  qml/AbstractItem.qml

  desktop.path = $$DATADIR/applications
  desktop.files += ../resources/$${TARGET}.desktop

  icon80.path = $$DATADIR/icons/hicolor/80x80/apps
  icon80.files += ../resources/$${TARGET}.png
  
  RESOURCES += \
    resources.qrc  
}
