import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: settingsListPage
    tools: settingsPageTools

    property int accountId: 0

    function setAccountId(id) {
        accountId = id;
    }

    onAccountIdChanged: {
        settingsList.setAccountId(accountId)
    }

    MouseArea {
        anchors.fill: parent
        enabled: pageStack.busy
    }

    SettingsListView {
         id: settingsList
         accountId: settingsListPage.accountId
         anchors.top: parent.top
     }

    QueryDialog {
        id: saveDialog
        message: "Saving is in progress"
        ProgressBar {
            id: saveProgressBar
            width: parent.width
            indeterminate: true
            value: 50
        }
    }

    ToolBarLayout {
        id: settingsPageTools
        visible: false
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                settingsPageMenu.close()
                pageStack.pop()
            }
        }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: {
                (settingsPageMenu.status == DialogStatus.Closed) ? settingsPageMenu.open() : settingsPageMenu.close()
            }
        }
    }

    SettingsPageMenu {
        id: settingsPageMenu

        onAboutClicked: {
            aboutDialog.open()
        }

        onSaveSettingsClicked: {
            (saveDialog.status == DialogStatus.Closed) ? saveDialog.open() : saveDialog.close()
        }
    }

    Component.onCompleted: settingsList.saveInProgress.connect(settingsPageMenu.saveSettingsClicked)
    AboutDialog {
        id: aboutDialog
    }
}
