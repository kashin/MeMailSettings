import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow
    color: "black"
    initialPage: MainPage {
        onAccountClicked: {
            pageStack.push(settingsListPage)
            settingsListPage.setAccountId(id)
        }
    }

    SettingsListPage {
        id: settingsListPage
    }

    Component.onCompleted: {
        theme.inverted = true;
    }
}
