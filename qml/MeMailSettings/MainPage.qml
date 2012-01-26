import QtQuick 1.1
import com.nokia.meego 1.0
Page {
     tools: commonTools
     Label {
         id: label
         anchors.centerIn: parent
         text: qsTr("Hello world!")
         visible: true
     }
}
