import QtQuick 1.1
import com.nokia.meego 1.0

AbstractItem {
    id: folderItem
    property int standardFolder: standardFolderRole
    signal itemClicked(int stFolder)

    onClicked: { folderItem.itemClicked(standardFolder) }

    itemLeftMargin: 15
    itemRightMargin: 15

    leftIconSource: model.iconForStandartFolderRole
    leftIconHeight: 64
    leftIconWidth: 64

    titleText: model.standardNameRole
    subtitleText: model.bindedFolderNameRole

    titleColor: "#FFFFBB"

    rightIconSource: "image://theme/meegotouch-combobox-indicator-inverted"
    rightIconHeight: 32
    rightIconWidth: 32
}
