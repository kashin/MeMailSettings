import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

Page {
    id: mainPage
    tools: mainTools

    Label {
        text: qsTr("Welcome to the MeMailSettings")
        font.pixelSize: 45
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        horizontalAlignment: Text.AlignHCenter
        anchors {
            horizontalCenter: parent.horizontalCenter
            left: parent.left
            right: parent.right
            bottom: buttonsColumn.top
            bottomMargin: 40
        }
    }

    onStatusChanged: { if (status == PageStatus.Activating) buttonsColumn.checkedButton = null }

    ButtonColumn {

        style: ButtonStyle {
            fontPixelSize: 40
            buttonWidth: mainPage.width
            buttonHeight: 80
            inverted: true
        }
        id: buttonsColumn
        anchors {
            right: parent.right
            left: parent.left
            leftMargin: 40
            rightMargin: 40
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        Button {
            id: makeGoodButton
            text: qsTr("Email Settings")
            onClicked: {
                pageStack.push(Qt.resolvedUrl("AccountsPage.qml"), { nextPageName: "EasyTweakPage.qml" })
            }
        }
        Button {
            id: foldersButton
            text: qsTr("Edit Folders")
            onClicked: {
                pageStack.push(Qt.resolvedUrl("AccountsPage.qml"), { nextPageName: "FoldersListPage.qml" })
            }
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
