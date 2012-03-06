import QtQuick 1.1
import com.nokia.meego 1.0

ListView {
    id: accountsListView
    anchors.fill: parent

    header: AccountsListHeader {
    }

    signal itemClicked(int accountId)

    model: accountsModel
    delegate: AccountsItem {
        Component.onCompleted: itemClicked.connect(accountsListView.itemClicked)
    }
}
