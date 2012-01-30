import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
     id: appWindow
     color: "black"
     initialPage: MainPage {
         onAccountClicked: {
             pageStack.push(settingsListPage, { accountId: id})
         }
     }

     ToolBarLayout {
         id: commonTools
         visible: false
         ToolIcon {
             platformIconId: "toolbar-view-menu"
             anchors.right: (parent === undefined) ? undefined : parent.right
             onClicked: (mainMenu.status == DialogStatus.Closed) ? mainMenu.open() : mainMenu.close()
         }
     }
     Menu {
         id: mainMenu
         visualParent: settingsListPage
         MenuLayout {
             MenuItem {
                 text: qsTr("Save settings")
             }
         }
     }
     SettingsListPage {
         id: settingsListPage
     }
}
