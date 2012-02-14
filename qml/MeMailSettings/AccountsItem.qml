import QtQuick 1.1
import com.nokia.meego 1.0


AbstractItem {
    id: accountsItem
    signal itemClicked(int accountId)
    property int accountId: 0

    onClicked: { accountsItem.itemClicked(accountId); }

    itemLeftMargin: 15
    itemRightMargin: 15

    leftIconSource: model.iconSource
    leftIconHeight: 64
    leftIconWidth: 64

    titleText: model.title
    subtitleText: model.subtitle

    rightIconSource: "image://theme/icon-m-common-drilldown-arrow-inverse"

    Component.onCompleted: accountId = accountIdRole
}
