import QtQuick 1.1

import com.nokia.meego 1.0
import com.nokia.extras 1.0

ListView {
    id: settingsList
    property int accountId: 0
    snapMode: ListView.SnapToItem
    function setAccountId(id)
    {
        accountId = id;
    }

    function saveSettings()
    {
        settingsModel.saveAccountSettings()
    }

    Component.onCompleted: settingsModel.saveInProgress.connect(settingsList.saveInProgress)

    signal saveInProgress(bool value)

    anchors.fill: parent

    model: settingsModel
    delegate: SettingsItem {
        onValueChanged: {
            settingsModel.valueChanged(settingsKey, settingsValue)
        }
    }

    header: Label {
        anchors.bottomMargin: 10
        text: "Settings list."
        font.pixelSize: 35
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    onAccountIdChanged: {
        settingsModel.setAccountId(accountId)
    }

    section {
        property: "groupRole"
        criteria: ViewSection.FullString
        delegate: SectionHeaderItem {sectionText: section}
    }

    SectionScroller {
        listView: settingsList
    }

    ScrollDecorator {
        flickableItem: settingsList
    }
}
