import QtQuick 1.1
import com.nokia.meego 1.0

Row {
    id: easyTweakItem
    width: parent.width
    anchors.topMargin: 25
    anchors.bottomMargin: 25
    anchors.horizontalCenter: parent.horizontalCenter
    state: "BooleanState"

    // properties
    property int settingsType: model.settingType

    // signals
    signal itemClicked(int index, bool checked, string value)

    Label {
        id: mainText
        text: model.title
        font.family: "Nokia Pure Text"
        font.pixelSize: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.rightMargin: 10
    }

    Switch {
        id: switcher
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        checked: model.settingValue
        onCheckedChanged: {
            // FIXME: This is a workaround, otherwhise
            // text field will be empty always when page is opened
            settingTextField.text = model.settingStringValue;
            easyTweakItem.saveSetting();
        }
    }

    TextField {
        id: settingTextField
        anchors.top: mainText.bottom
        anchors.right: saveSettingButton.left
        anchors.left: parent.left
        anchors.topMargin: 30
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        text: ""
    }

    Button {
        id: saveSettingButton
        anchors.top: mainText.bottom
        anchors.right: parent.right
        anchors.topMargin: 30
        anchors.bottomMargin: 30
        anchors.verticalCenter: settingTextField.verticalCenter
        text: qsTr("Save Setting")
        onClicked: {
            easyTweakItem.saveSetting();
        }
    }

    // states

    states: [
        State {
            name: "BooleanState"
            PropertyChanges { target: settingTextField; height: -1}
            PropertyChanges { target: settingTextField; text: ""}
            PropertyChanges { target: saveSettingButton; height: -1}
            PropertyChanges { target: saveSettingButton; text: ""}
        },
        State {
            name: "StringStateEnabled"
            PropertyChanges { target: settingTextField; height: 40}
            PropertyChanges { target: settingTextField; text: model.settingStringValue}
            PropertyChanges { target: saveSettingButton; height: 35}
            PropertyChanges { target: saveSettingButton; text: qsTr("Save Setting")}
        },
        State {
            name: "StringStateDisabled"
            PropertyChanges { target: settingTextField; height: -1}
            PropertyChanges { target: settingTextField; text: model.settingStringValue}
            PropertyChanges { target: saveSettingButton; height: -1}
            PropertyChanges { target: saveSettingButton; text: ""}
        }
    ]

    // functions
    function saveSetting() {
        if (model.tweakType === 0) // boolean setting
        {
            easyTweakItem.itemClicked(settingsType, switcher.checked, "");
            easyTweakItem.state = "BooleanState";
        }
        else if (model.tweakType === 1) //string setting
        {
            easyTweakItem.itemClicked(settingsType, switcher.checked, settingTextField.text);
            easyTweakItem.state = switcher.checked ? "StringStateEnabled" : "StringStateDisabled";
        }
    }
}
