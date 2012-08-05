import QtQuick 1.1
import com.nokia.meego 1.0

QueryDialog {
    id: aboutDialog
    message: "<html>
        <style>
        a {
                font-weight: bold;
                color: #00a8df;
                text-decoration: underline;
        }
        </style>
        <body>
         <p align='center'>
          MeMail Settings.<br/>
          Author(s): Sergey Kashin, Anton Magaev<br/>
          For more info please visit <a href='http:\/\/kashin.github.com\/MeMailSettings\/'>MeMailSettings support page</a>
         </p>
        </body>
        </html>"
    onLinkActivated: {
        Qt.openUrlExternally(link);
    }

    acceptButtonText: "Ok"
}
