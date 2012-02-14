import QtQuick 1.1
import com.nokia.meego 1.0

// now only inverted style is supported

Item {
    id: item

    signal clicked
    property alias pressed: mouseArea.pressed

    property int itemHeight: 80
    property int itemLeftMargin: 10
    property int itemRightMargin: 0

    property int leftIconHeight: -1
    property int leftIconWidth: -1
    property string leftIconSource: ""

    property alias titleText: mainText.text
    property int titleSize: 26

    property alias subtitleText: subText.text
    property int subtitleSize: 22

    property int rightIconHeight: -1
    property int rightIconWidth: -1
    property string rightIconSource: ""

    property int titleWeight: Font.Bold
    property int subtitleWeight: Font.Normal

    property color titleColor: "#ffffff"
    property color titleColorPressed: "#797979"

    property color subtitleColor: "#C8C8C8"
    property color subtitleColorPressed: "#797979"

    height: itemHeight
    width: parent.width

    BorderImage {
        id: background
        anchors.fill: parent
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-panel-inverted-background-pressed"
    }

    Row {
        anchors.fill: parent
        anchors.leftMargin: itemLeftMargin
        anchors.rightMargin: itemRightMargin
        spacing: 16

        Image {
            anchors.verticalCenter: parent.verticalCenter
            visible: source !=""
            width: leftIconWidth == -1 ? sourceSize.width : leftIconWidth
            height: leftIconHeight == -1 ? sourceSize.height : leftIconHeight
            source: leftIconSource
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter

            Label {
                id: mainText
                text: ""
                font.family: "Nokia Pure Text"
                font.weight: item.titleWeight
                font.pixelSize: item.titleSize
                color: mouseArea.pressed ? item.titleColorPressed : item.titleColor
            }

            Label {
                id: subText
                text: ""
                font.family: "Nokia Pure Text Light"
                font.weight: item.subtitleWeight
                font.pixelSize: item.subtitleSize
                color: mouseArea.pressed ? item.subtitleColorPressed : item.subtitleColor
                visible: text != ""
            }
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            visible: source !=""
            anchors.right: parent.right
            width: rightIconWidth == -1 ? sourceSize.width : rightIconWidth
            height: rightIconHeight == -1 ? sourceSize.height : rightIconHeight
            source: rightIconSource
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            item.clicked();
        }
    }
}
