import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow
    color: "black"
    initialPage: MainPage {
    }

    Component.onCompleted: {
        theme.inverted = true;
    }
    onOrientationChangeFinished: {
           showStatusBar = inPortrait;
    }
}
