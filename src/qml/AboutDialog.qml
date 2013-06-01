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
          Most probably it is a last update of a MeMailSettings, so if you like this application, it helped you
          and/or you want to thank developers, then you can easily click a Donate button on a support page :)<br/>
          For more info please visit <a href='http:\/\/kashin.github.com\/MeMailSettings\/'>MeMailSettings support page</a>.
          Thank you!
         </p>
        </body>
        </html>"
    onLinkActivated: {
        Qt.openUrlExternally(link);
    }

    acceptButtonText: "Ok"
}
