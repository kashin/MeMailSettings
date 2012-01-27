import QtQuick 1.0

import com.nokia.meego 1.0

Row {
    Image {
        id: providersIcon
        source: "image://theme/" + iconRole
    }
    Text {
        id: providersLabel
        anchors.left: providersIcon.right
        text: displayNameRole
        color: "blue"
        font.pixelSize: 30
    }
}
