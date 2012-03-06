import QtQuick 1.1
import com.nokia.meego 1.0

Row {
    id: easyTweakItem
    property int settingsType: model.settingType
    signal itemClicked(int index, bool checked)
    width: parent.width
    anchors.topMargin: 20
    anchors.bottomMargin: 20

    Label {
        id: mainText
        text: model.title
        font.family: "Nokia Pure Text"
        font.pixelSize: 25
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
            easyTweakItem.itemClicked(easyTweakItem.settingsType, switcher.checked);
        }
    }
}
