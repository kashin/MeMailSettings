import QtQuick 1.0
import com.nokia.meego 1.0

Menu {
    id: settingsPageMenu
    signal aboutClicked()
    signal saveSettingsClicked()
    MenuLayout {
        MenuItem {
            text: qsTr("Save Settings")
            onClicked:
                saveSettingsClicked()
        }

        MenuItem {
            text: qsTr("About")
            onClicked: aboutClicked()
        }
    }
}
