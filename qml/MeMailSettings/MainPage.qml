import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: mainPage
    tools: commonTools
    signal accountClicked(int id)

    MouseArea {
        anchors.fill: parent
        enabled: pageStack.busy
    }
    AccountsListView {
        id: accountsList
        anchors.top: parent.top
        Component.onCompleted: itemClicked.connect(mainPage.accountClicked)
    }
}
