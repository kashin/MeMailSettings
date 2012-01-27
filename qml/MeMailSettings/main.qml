import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
     id: appWindow
     color: "blue"
     initialPage: mainPage

     MainPage {
         id: mainPage
     }

     ToolBarLayout {
         id: commonTools
         visible: true
         ToolIcon {
             platformIconId: "toolbar-view-menu"
             anchors.right: (parent === undefined) ? undefined : parent.right
             onClicked: (mainMenu.status == DialogStatus.Closed) ? mainMenu.open() : mainMenu.close()
         }
     }
     Menu {
         id: mainMenu
         visualParent: pageStack
         MenuLayout {
             MenuItem {
                 text: qsTr("Some menu item")
             }
         }
     }
}
