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
           accountslistmodel.cpp

HEADERS += mainview.h \
           accountsettingsreader.h \
           accountslistmodel.h

OTHER_FILES += ../qml/MeMailSettings/main.qml \
                ../qml/MeMailSettings/MainPage.qml \
                ../qml/MeMailSettings/AccountsListView.qml \
                ../qml/MeMailSettings/AccountsItem.qml


qml_files.files += ../qml/MeMailSettings/main.qml \
                   ../qml/MeMailSettings/MainPage.qml \
                   ../qml/MeMailSettings/AccountsListView.qml \
                   ../qml/MeMailSettings/AccountsItem.qml
qml_files.path = $$INSTALL_QML_ROOT
INSTALLS += qml_files
