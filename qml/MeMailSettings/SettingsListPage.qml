import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: settingsListPage
    property int accountId: 0
    tools: commonTools
    color: "black"

    MouseArea {
        anchors.fill: parent
        enabled: pageStack.busy
    }

    SettingsListView {
         id: settingsList
         accountId: settingsListPage.accountId
         anchors.top: parent.top
     }

    Button {
        anchors.bottom: parent.bottom
        text: "Go Back"
        onClicked: pageStack.pop(settingsListPage)
    }

    onAccountIdChanged: {
        settingsList.setAccountId(accountId)
    }
}
