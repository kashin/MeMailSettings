TEMPLATE = app
QT += declarative
TARGET = memailsettings
#CONFIG +=
PKGCONFIG += qmfclient accounts-qt

QMAKE_CXXFLAGS *= -Werror \
    -O2

SOURCES += main.cpp \
           mainview.cpp

HEADERS += mainview.h

OTHER_FILES += ../qml/MeMailSettings/main.qml
