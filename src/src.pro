TEMPLATE = app
QT += declarative
TARGET = memailsettings

target.path = $$INSTALL_ROOT/bin

INSTALLS += target

CONFIG += link_pkgconfig
PKGCONFIG += qmfclient accounts-qt

QMAKE_CXXFLAGS *= -Werror \
    -O2

SOURCES += main.cpp \
           mainview.cpp \
    accountsettingsreader.cpp

HEADERS += mainview.h \
    accountsettingsreader.h

OTHER_FILES += ../qml/MeMailSettings/main.qml \
                ../qml/MeMailSettings/MainPage.qml
