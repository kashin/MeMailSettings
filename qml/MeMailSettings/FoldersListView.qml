import QtQuick 1.1
import com.nokia.meego 1.0

ListView {
    id: foldersListView
    property int selectedId: 0
    anchors.fill: parent

    Component {
        id: headerComponent
        Item{
            width: parent.width
            height: childrenRect.height
            Label {
                id: foldersListLabel
                anchors.top: parent.top
                anchors.topMargin: 10
                text: qsTr("Email Folders")
                color: "white"
                font.pixelSize: 32
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
            Image {
                id: separator
                anchors.top: foldersListLabel.bottom
                anchors.topMargin: 8
                anchors {
                    right: parent.right
                    left: parent.left
                }
                source: "image://theme/meegotouch-groupheader-inverted-background"
            }
        }
    }

    SelectionDialog {
        id: selectionDialog
        function setAccountId(accountId)
        {
            accountsFoldersModel.setAccountId(accountId)
        }

        model: accountsFoldersModel
    }

    header: headerComponent

    model: foldersModel
    delegate: FoldersItem {
        onItemClicked: {
            selectionDialog.titleText = foldersModel.getStandardFolderName(stFolder)
            selectionDialog.open()
        }
    }

    onSelectedIdChanged: {
        foldersModel.setAccountId(selectedId)
        selectionDialog.setAccountId(selectedId)
    }
}
