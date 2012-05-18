import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: configPage
    tools: configTools

    ToolBarLayout {
        id: configTools
        visible: false
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                configPageMenu.close()
                pageStack.pop()
            }
        }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: {
                (configPageMenu.status == DialogStatus.Closed) ? configPageMenu.open() : configPageMenu.close()
            }
        }
    }
    MainMenu {
        id: configPageMenu
        onAboutClicked: {
            aboutDialog.open()
        }
    }
    AboutDialog {
        id: aboutDialog
    }
}
