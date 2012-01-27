import QtQuick 1.1

import com.nokia.meego 1.0

ListView {
    anchors.fill: parent

    model: accountsModel
    delegate: AccountsItem {
    }
}
