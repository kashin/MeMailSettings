import QtQuick 1.0
import com.nokia.extras 1.0

ListDelegate {
    id: accountsItem
    signal itemClicked(int accountId)
    property int accountId: 0

    onClicked: { accountsItem.itemClicked(accountId); }

    // right arrow
    Image {
        id: image
        anchors.rightMargin: 15
        anchors { verticalCenter: accountsItem.verticalCenter; right: parent.right }
        source: "image://theme/icon-m-common-drilldown-arrow-inverse"
    }

    Component.onCompleted: accountId = accountIdRole
}
