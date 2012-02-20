import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: foldersPage
    tools: foldersTools
    property alias accountId: foldersList.selectedId

    FoldersListView {
        id: foldersList
        anchors.top: parent.top
    }

    ToolBarLayout {
        id: foldersTools
        visible: false
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                foldersPageMenu.close()
                pageStack.pop()
            }
        }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: {
                (foldersPageMenu.status == DialogStatus.Closed) ? foldersPageMenu.open() : foldersPageMenu.close()
            }
        }
    }
    MainMenu {
        id: foldersPageMenu
        onAboutClicked: {
            aboutDialog.open()
        }
    }
    AboutDialog {
        id: aboutDialog
    }
}
