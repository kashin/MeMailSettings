import QtQuick 1.1
import com.nokia.meego 1.0

ListView {
    id: accountsListView
    anchors.fill: parent
    property bool editSettingsMode: true

    Component {
        id: headerComponent
        Item{
            id: headerItem
            width: parent.width
            height: accountsListLabel.height + separator.height + accountsListLabel.anchors.topMargin + separator.anchors.topMargin
            property alias labelText: accountsListLabel.text
            Label {
                id: accountsListLabel
                anchors.top: parent.top
                anchors.topMargin: 10
                text: "Email Accounts. " + parent.editSettingsMode ? qsTr("Edit Settings mode") : qsTr("Edit Folders mode")
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

    onEditSettingsModeChanged: {
        header.labelText = "Email Accounts. " + editSettingsMode ? qsTr("Edit Settings mode") : qsTr("Edit Folders mode")
    }
}
