import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: easyTweakPage
    tools: easyTweakTools
    property alias accountId: easyTweakList.selectedId

    EasyTweakList {
        id: easyTweakList
        anchors.top: parent.top
    }

    ToolBarLayout {
        id: easyTweakTools
        visible: false
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                easyTweakPageMenu .close()
                pageStack.pop()
            }
        }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: {
                (easyTweakPageMenu.status == DialogStatus.Closed) ? easyTweakPageMenu.open() : easyTweakPageMenu.close()
            }
        }
    }
    MainMenu {
        id: easyTweakPageMenu
        onAboutClicked: {
            aboutDialog.open()
        }
    }
    AboutDialog {
        id: aboutDialog
    }
}
