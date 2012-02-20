import QtQuick 1.1

import com.nokia.meego 1.0

Row {
    id: settingsItem
    width: parent.width
    height: childrenRect.height
    anchors.topMargin: 40
    anchors.bottomMargin: 40

    property string key: keyRole
    property string value: valueRole

    signal valueChanged(string settingsKey, string settingsValue)

    Label {
        id: settingsLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10
        text: keyRole
        style: LabelStyle {
            fontPixelSize: 28
        }
        wrapMode: Text.WordWrap
    }

    TextField {
        id: settingsEditField
        anchors.top: settingsLabel.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 10
        width: parent.width - 10
        text:  valueRole
        focus: false
        onTextChanged: settingsItem.valueChanged(settingsLabel.text, settingsEditField.text)
    }
}
