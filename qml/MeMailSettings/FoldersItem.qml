import QtQuick 1.0
import com.nokia.meego 1.0

Item {
    id: foldersItem
    height: childrenRect.height
    width: parent.width
    property int standardFolder: standardFolderRole
    signal itemClicked(int stFolder)

    anchors {
        topMargin: 10
        bottomMargin: 10
    }
    Label {
        id: titleLabel
        font.pixelSize: 30
        text: standardNameRole
        color: "darkblue"
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            topMargin: 10
            bottomMargin: 10
        }
    }
    Label {
        id: subtitleLabel
        font.pixelSize: 20
        text: bindedFolderNameRole
        anchors {
            top: titleLabel.bottom
            horizontalCenter: parent.horizontalCenter
            topMargin: 10
            bottomMargin: 10
        }
    }
    Image {
        id: separator
        anchors
        {
            right: parent.right
            left: parent.left
            top: subtitleLabel.bottom
            topMargin: 10
            bottomMargin: 10
        }
        source: "image://theme/meegotouch-groupheader-inverted-background"
    }
    MouseArea {
        id: itemMouseArea
        anchors.fill: parent
        onClicked: {
            itemClicked(standardFolder)
        }
    }
}
