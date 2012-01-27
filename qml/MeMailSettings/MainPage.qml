import QtQuick 1.1
import com.nokia.meego 1.0

Page {
     tools: commonTools
     Text {
         anchors.top: parent.top
         text: "Some label"
         color: "green"
         font.pixelSize: 15
     }
     AccountsListView {
     }
}
