import QtQuick 1.0

import com.nokia.meego 1.0

Row {
    id: accountsItem
    anchors.topMargin: 20
    height: providersIcon.height
    width: parent.width
    Image {
        id: providersIcon
        source: "image://theme/" + iconRole
        anchors.bottomMargin: 10
    }

    Label {
        id: providersLabel
        anchors.left: providersIcon.right
        anchors.verticalCenter: providersIcon.verticalCenter
        height: providersIcon.height
        text: displayNameRole
        style: LabelStyle {
            fontPixelSize: providersIcon.height - 30
        }

        wrapMode: Text.WordWrap
    }

    signal itemClicked(int accountId)
    property int accountId: 0


    Component.onCompleted: accountId = accountIdRole

    MouseArea {
        anchors.fill: providersLabel
        onClicked: {
            accountsItem.itemClicked(accountId);
        }
    }
}
