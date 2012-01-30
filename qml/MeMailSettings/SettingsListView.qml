import QtQuick 1.1

import com.nokia.meego 1.0

ListView {
    property int accountId: 0

    function setAccountId(id)
    {
        accountId = id;
    }

    anchors.fill: parent

    model: settingsModel
    delegate: SettingsItem {
    }

    header: Label {
        id: settingsListLabel
        anchors.top: parent.top
        anchors.bottomMargin: 10
        text: "Settings list."
        color: "black"
        font.pixelSize: 35
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    onAccountIdChanged: {
        settingsModel.setAccountId(accountId)
    }

}
