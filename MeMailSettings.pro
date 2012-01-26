TEMPLATE = subdirs
SUBDIRS = src

desktop_file.files = MeMailSettings.desktop
desktop_file.path = $$INSTALL_ROOT/share/applications
INSTALLS += desktop_file

OTHER_FILES += MailDebugSettings.desktop
