import QtQuick 1.0

import com.nokia.meego 1.0

Row {
    id: accountsItem
    Image {
        id: providersIcon
        source: "image://theme/" + iconRole
    }

    Label {
        id: providersLabel
        anchors.left: providersIcon.right
        height: providersIcon.height
        text: displayNameRole
        wrapMode: Text.WordWrap
        platformStyle: LabelStyle {
            textColor: "blue"
            fontFamily: "Arial"
            fontPixelSize: providersIcon.height - 15
        }
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
