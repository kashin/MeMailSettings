import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    width: parent.width
    height: childrenRect.height
    property alias sectionText: sectionLabel.text

    Label {
        id: sectionLabel
        anchors {right: parent.right}
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        color: "white"
        font.pixelSize: 25
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    Image {
        id: separator
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors {right: sectionLabel.left ; left: parent.left}
        source: "image://theme/meegotouch-groupheader-inverted-background"
    }
}
