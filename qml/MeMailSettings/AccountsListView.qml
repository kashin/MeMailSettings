import QtQuick 1.1

import com.nokia.meego 1.0

ListView {
    header: Label {
        id: accountsListLabel
        anchors.top: parent.top
        text: "Accounts list. Choose account to edit."
        color: "black"
        font.pixelSize: 30
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    anchors.fill: parent
    anchors.bottomMargin: 10

    model: accountsModel
    delegate: AccountsItem {
    }
}
