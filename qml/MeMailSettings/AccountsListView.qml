import QtQuick 1.1

import com.nokia.meego 1.0

ListView {
    id: accountsListView
    header: Label {
        id: accountsListLabel
        anchors.top: parent.top
        text: "Accounts list. Choose account to edit."
        color: "black"
        font.pixelSize: 25
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    anchors.fill: parent
    anchors.bottomMargin: 10

    signal itemClicked(int accountId)

    model: accountsModel
    delegate: AccountsItem {
        Component.onCompleted: itemClicked.connect(accountsListView.itemClicked)
    }
}
