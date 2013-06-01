import QtQuick 1.1
import com.nokia.meego 1.0

Row {
    id: easyTweakItem
    width: parent.width
    anchors.topMargin: 25
    anchors.bottomMargin: 25
    anchors.horizontalCenter: parent.horizontalCenter
    height: 75
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
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 20
        anchors.bottomMargin: 20
    }

    Switch {
        id: switcher
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        checked: model.settingValue
        onCheckedChanged: {
            // FIXME: This is a workaround, otherwhise
            // text field will be empty always when page is opened
            settingTextField.text = model.settingStringValue;
            easyTweakItem.saveSetting();
        }
    }

    DropDown {
        id: settingDropDown
        height: 40
        anchors.top: switcher.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.topMargin: 30
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        value: model.settingStringValue

        onValueChanged: {
            easyTweakItem.saveSetting()
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

    Label {
        id: warningText
        text: model.settingWarningStringValue
        font.family: "Nokia Pure Text"
        font.pixelSize: 24
        anchors.top: settingTextField.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 20
        anchors.bottomMargin: 20
    }

    Image {
        id: separator
        anchors.bottom: parent.bottom
        anchors.topMargin: 8
        anchors {right: parent.right ; left: parent.left}
        source: "image://theme/meegotouch-groupheader-inverted-background"
    }

    // states

    states: [
        State {
            name: "BooleanState"
            PropertyChanges { target: easyTweakItem;  height: 75 }
            PropertyChanges { target: settingTextField; height: -1}
            PropertyChanges { target: settingTextField; text: ""}
            PropertyChanges { target: saveSettingButton; height: -1}
            PropertyChanges { target: saveSettingButton; text: ""}
            PropertyChanges { target: settingDropDown;  enabled: false }
            PropertyChanges { target: warningText;  height: -1 }
            PropertyChanges { target: warningText;  text: "" }
        },
        State {
            name: "DropDownStateEnabled"
            PropertyChanges { target: easyTweakItem;  height: 150 }
            PropertyChanges { target: settingTextField; height: -1}
            PropertyChanges { target: settingTextField; text: ""}
            PropertyChanges { target: saveSettingButton; height: -1}
            PropertyChanges { target: saveSettingButton; text: ""}
            PropertyChanges { target: settingDropDown; enabled: true }
            PropertyChanges { target: warningText;  height: -1 }
            PropertyChanges { target: warningText;  text: "" }
        },
        State {
            name: "DropDownStateDisabled"
            PropertyChanges { target: easyTweakItem;  height: 75 }
            PropertyChanges { target: settingTextField; height: -1}
            PropertyChanges { target: settingTextField; text: ""}
            PropertyChanges { target: saveSettingButton; height: -1}
            PropertyChanges { target: saveSettingButton; text: ""}
            PropertyChanges { target: settingDropDown;  enabled: false }
            PropertyChanges { target: warningText;  height: -1 }
            PropertyChanges { target: warningText;  text: "" }
        },
        State {
            name: "StringStateEnabled"
            PropertyChanges { target: easyTweakItem;  height: 75 }
            PropertyChanges { target: settingTextField; height: 40}
            PropertyChanges { target: settingTextField; text: model.settingStringValue}
            PropertyChanges { target: saveSettingButton; height: 35}
            PropertyChanges { target: saveSettingButton; text: qsTr("Save Setting")}
            PropertyChanges { target: settingDropDown; enabled: false}
            PropertyChanges { target: warningText;  height: -1 }
            PropertyChanges { target: warningText;  text: "" }
        },
        State {
            name: "StringStateDisabled"
            PropertyChanges { target: easyTweakItem;  height: 75 }
            PropertyChanges { target: settingTextField; height: -1}
            PropertyChanges { target: settingTextField; text: model.settingStringValue}
            PropertyChanges { target: saveSettingButton; height: -1}
            PropertyChanges { target: saveSettingButton; text: ""}
            PropertyChanges { target: settingDropDown; enabled: false}
            PropertyChanges { target: warningText;  height: -1 }
            PropertyChanges { target: warningText;  text: "" }
        },
        State {
            name: "WarningStringStateEnabled"
            PropertyChanges { target: easyTweakItem;  height: 270 }
            PropertyChanges { target: settingTextField; height: 40}
            PropertyChanges { target: settingTextField; text: model.settingStringValue}
            PropertyChanges { target: saveSettingButton; height: 35}
            PropertyChanges { target: saveSettingButton; text: qsTr("Save Setting")}
            PropertyChanges { target: settingDropDown; enabled: false}
            PropertyChanges { target: warningText;  height: 35 }
            PropertyChanges { target: warningText;  text: model.settingWarningStringValue }
        },
        State {
            name: "WarningStringStateDisabled"
            PropertyChanges { target: easyTweakItem;  height: 75 }
            PropertyChanges { target: settingTextField; height: -1}
            PropertyChanges { target: settingTextField; text: model.settingStringValue}
            PropertyChanges { target: saveSettingButton; height: -1}
            PropertyChanges { target: saveSettingButton; text: ""}
            PropertyChanges { target: settingDropDown; enabled: false}
            PropertyChanges { target: warningText;  height: -1 }
            PropertyChanges { target: warningText;  text: "" }
        }
    ]

    // functions
    function saveSetting() {
        if (model.tweakType === 0) // boolean setting
        {
            easyTweakItem.itemClicked(settingsType, switcher.checked, "");
            easyTweakItem.state = "BooleanState";
        }
        else if (model.tweakType === 1) //enum setting
        {
            if (settingDropDown.text === "No value" || settingDropDown.value === "") {
                easyTweakItem.itemClicked(settingsType, switcher.checked, "");
            } else {
                easyTweakItem.itemClicked(settingsType, switcher.checked, settingDropDown.text);
            }

            if (switcher.checked) {
                easyTweakItem.state = "DropDownStateEnabled";
            } else {
                easyTweakItem.state = "DropDownStateDisabled";
            }
        }
        else if (model.tweakType === 2) //string setting
        {
            easyTweakItem.itemClicked(settingsType, switcher.checked, settingTextField.text);
            easyTweakItem.state = switcher.checked ? "StringStateEnabled" : "StringStateDisabled";
        }
        else if (model.tweakType === 3) // int with warning setting
        {
            easyTweakItem.itemClicked(settingsType, switcher.checked, settingTextField.text);
            easyTweakItem.state = switcher.checked ? "WarningStringStateEnabled" : "WarningStringStateDisabled";
        }
    }

    Component.onCompleted: {
        if (model.tweakType === 0) // boolean setting
        {
            easyTweakItem.state = "BooleanState";
        }
        else if (model.tweakType === 1) //enum setting
        {
            if (switcher.checked) {
                easyTweakItem.state = "DropDownStateEnabled";
            } else {
                easyTweakItem.state = "DropDownStateDisabled";
            }
            settingDropDown.value = model.settingStringValue;
        }
        else if (model.tweakType === 2) //string setting
        {
            easyTweakItem.state = switcher.checked ? "StringStateEnabled" : "StringStateDisabled";
        }
        else if (model.tweakType === 3) { // int with warning setting
            easyTweakItem.state = switcher.checked ? "WarningStringStateEnabled" : "WarningStringStateDisabled";
        }
    }
}
