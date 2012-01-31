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

     Component.onCompleted: {
         theme.inverted = true;
     }


     ToolBarLayout {
         id: commonTools
         visible: false
         ToolIcon {
             iconId: "toolbar-back"
             onClicked: {
                 mainMenu.close()
                 pageStack.pop()
             }
         }
         ToolIcon {
             platformIconId: "toolbar-view-menu"
             anchors.right: (parent === undefined) ? undefined : parent.right
             onClicked: (mainMenu.status == DialogStatus.Closed) ? mainMenu.open() : mainMenu.close()
         }
     }
     Menu {
         id: mainMenu
         MenuLayout {
             MenuItem {
                 text: qsTr("Сделать добро!")
             }
         }
     }
     SettingsListPage {
         id: settingsListPage
     }
}
