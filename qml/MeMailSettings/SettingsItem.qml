import QtQuick 1.0

import com.nokia.meego 1.0

Row {
    Label {
        id: settingsLabel
        anchors.left: parent.left
        text: keyRole
        platformStyle: LabelStyle {
            textColor: "black"
            fontFamily: "Arial"
            fontPixelSize: 25
            inverted: true
        }
    }
    TextEdit {
        id: settingsEditField
        anchors.right: parent.right
        text:  valueRole
        font.pointSize: 25
        color: "red"
        focus: false
    }
}
