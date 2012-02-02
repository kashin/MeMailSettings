import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: mainPage
    tools: mainTools

    signal accountClicked(int id)

    MouseArea {
        anchors.fill: parent
        enabled: pageStack.busy
    }
    AccountsListView {
        id: accountsList
        anchors.top: parent.top
        Component.onCompleted: itemClicked.connect(mainPage.accountClicked)
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
