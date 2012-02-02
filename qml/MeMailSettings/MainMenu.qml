import QtQuick 1.0
import com.nokia.meego 1.0

Menu {
    id: mainMenu

    signal aboutClicked()
    MenuLayout {
        MenuItem {
            text: qsTr("About")
            onClicked: aboutClicked()
        }
    }
}
