import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

Page {
    id: mainPage
    tools: mainTools

    ButtonColumn {
        id: buttonsColumn
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        Button {
            id: settingsButton
            text: qsTr("Edit Settings")
            onClicked: {
                pageStack.push(Qt.resolvedUrl("AccountsPage.qml"), { showSettings: true })
            }
        }
        Button {
            id: foldersButton
            text: qsTr("Edit Folders")
            onClicked: {
                pageStack.push(Qt.resolvedUrl("AccountsPage.qml"), { showSettings: false })
            }
        }
        Button {
            id: makeGoodButton
            text: qsTr("Make Good!")
        }
    }

    ToolBarLayout {
        id: mainTools
        visible: false
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: {
                (mainMenu.status == DialogStatus.Closed) ? mainMenu.open() : mainMenu.close()
            }
        }
    }
    MainMenu {
        id: mainMenu
        onAboutClicked: {
            aboutDialog.open()
        }
    }
    AboutDialog {
        id: aboutDialog
    }
}
