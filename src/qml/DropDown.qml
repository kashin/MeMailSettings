import QtQuick 1.1
import com.nokia.meego 1.0

Rectangle {
    id: dropDown
    color: "black"
    property alias text: dropDownButton.text
    property string value: ""
    property bool enabled: true

    Button {
        id: dropDownButton
        width: parent.width
        height: 50;
        anchors.centerIn: parent

        text: dropDownDialog.model.get(0).name
        onClicked: dropDownDialog.open();

        ToolIcon {
            id: filterImage
            height: 25
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            platformIconId: "icon-m-textinput-combobox-arrow"
        }

        SelectionDialog {
            id: dropDownDialog
            height: 50
            titleText: "Select protocol version"

            // ToDo replace it with C++ model to be able to show only supported (by account's server) protocol versions.
            // Is it possible to get from the accounts DB?
            model: ListModel {
                ListElement { name: "No value" }
                ListElement { name: "2.5" }
                ListElement { name: "12.0" }
                ListElement { name: "12.1" }
                ListElement { name: "14.0" }
                ListElement { name: "14.1" }
            }
            onAccepted: {
                dropDown.value = dropDownDialog.model.get(dropDownDialog.selectedIndex).name;
            }
        }
    }

    onEnabledChanged: {
        if (enabled) {
            filterImage.height = 25;
            filterImage.platformIconId = "icon-m-textinput-combobox-arrow";
            dropDownButton.height = 50;
            height = 50;
            text = value;
        } else {
            filterImage.height = -1;
            filterImage.platformIconId = "";
            dropDownButton.height = -1;
            height = -1;
            text = "";
        }
    }

    onValueChanged: {
        text = value;
    }
}
