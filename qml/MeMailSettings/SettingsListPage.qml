import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: settingsListPage
    property int accountId: 0
    tools: commonTools

    function setAccountId(id) {
        accountId = id;
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

    onAccountIdChanged: {
        settingsList.setAccountId(accountId)
    }
}
