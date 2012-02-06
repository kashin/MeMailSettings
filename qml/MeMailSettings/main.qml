import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow
    color: "black"
    initialPage: MainPage {
        onAccountClicked: {
            pageStack.push(Qt.resolvedUrl("SettingsListPage.qml"), {accountId: id})
        }
    }

    Component.onCompleted: {
        theme.inverted = true;
    }
}
