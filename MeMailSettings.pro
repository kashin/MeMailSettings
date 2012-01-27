TEMPLATE = subdirs
SUBDIRS = src


OTHER_FILES += MailDebugSettings.desktop \

desktop_file.files = MeMailSettings.desktop
desktop_file.path = $$INSTALL_ROOT/share/applications
INSTALLS += desktop_file
