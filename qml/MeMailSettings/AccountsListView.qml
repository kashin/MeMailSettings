import QtQuick 1.1
import com.nokia.meego 1.0

ListView {
    id: accountsListView
    anchors.fill: parent

    Component {
        id: headerComponent
        Item{
            width: parent.width
            height: accountsListLabel.height + separator.height + accountsListLabel.anchors.topMargin + separator.anchors.topMargin
            Label {
                id: accountsListLabel
                anchors.top: parent.top
                anchors.topMargin: 10
                text: "Accounts"
                color: "white"
                font.pixelSize: 32
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
            Image {
                id: separator
                anchors.top: accountsListLabel.bottom
                anchors.topMargin: 8
                anchors {right: parent.right ; left: parent.left}
                source: "image://theme/meegotouch-groupheader-inverted-background"
            }
        }
    }

    header: headerComponent

    signal itemClicked(int accountId)

    model: accountsModel
    delegate: AccountsItem {
        Component.onCompleted: itemClicked.connect(accountsListView.itemClicked)
    }
}
