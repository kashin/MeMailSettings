import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: mainPage
    tools: mainTools
    property string nextPageName: "SettingsListPage.qml"
    property bool showOnlyMfE: false

    signal accountClicked(int id)

    AccountsListView {
        id: accountsList
        anchors.top: parent.top
        Component.onCompleted: itemClicked.connect(mainPage.accountClicked)
    }

    ToolBarLayout {
        id: mainTools
        visible: false
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                accountsPageMenu.close()
                pageStack.pop()
            }
        }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: {
                (accountsPageMenu.status === DialogStatus.Closed) ? accountsPageMenu.open() : accountsPageMenu.close()
            }
        }
    }
    MainMenu {
        id: accountsPageMenu
        onAboutClicked: {
            aboutDialog.open()
        }
    }
    AboutDialog {
        id: aboutDialog
    }

    onAccountClicked: {
        pageStack.push(Qt.resolvedUrl(nextPageName), {accountId: id})
    }

    onShowOnlyMfEChanged: {
        accountsList.showOnlyMfE = showOnlyMfE;
    }
    Component.onCompleted: {
        accountsList.showOnlyMfE = showOnlyMfE;
    }
}
