TEMPLATE = subdirs
SUBDIRS = src


OTHER_FILES += MailDebugSettings.desktop \

desktop_file.files = MeMailSettings.desktop
desktop_file.path = $$INSTALL_ROOT/share/applications
INSTALLS += desktop_file

qml_files.files = qml/MeMailSettings/main.qml qml/MeMailSettings/MainPage.qml
qml_files.path = $$INSTALL_QML_ROOT
INSTALLS += qml_files
