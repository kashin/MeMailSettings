import QtQuick 1.0
import com.nokia.meego 1.0

Item {
    id: foldersItem
    height: childrenRect.height
    width: parent.width

    Label {
        id: titleLabel
        text: standardNameRole
        anchors {
            horizontalCenter: parent.horizontalCenter
            topMargin: 10
            bottomMargin: 10
        }
    }
    Label {
        id: subtitleLabel
        text: bindedFolderNameRole
        anchors {
            top: titleLabel.bottom
            horizontalCenter: parent.horizontalCenter
            topMargin: 10
            bottomMargin: 10
        }
    }
}
