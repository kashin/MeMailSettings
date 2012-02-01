import QtQuick 1.1

import com.nokia.meego 1.0

ListView {
    id: settingsList
    property int accountId: 0

    function setAccountId(id)
    {
        accountId = id;
    }

    anchors.fill: parent

    model: settingsModel
    delegate: SettingsItem {
        onSaveSetting: {
            settingsModel.saveAccountSetting(settingsKey, settingsValue)
        }
    }

    header: Label {
        id: settingsListLabel
        anchors.bottomMargin: 10
        anchors.horizontalCenter: settingsList.horizontalCenter
        text: "Settings list."
        font.pixelSize: 35
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    onAccountIdChanged: {
        settingsModel.setAccountId(accountId)
    }

}
