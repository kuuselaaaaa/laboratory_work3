import QtQuick 2.12
import QtQuick.Controls 2.12


// панель снизу, показывает размер и дату модификации файла
Item {
    height: 32

    // данные для показа
    property string fsize: ""
    property string fdate: ""

    function setSize(s) {
        fsize = s
    }

    function setDate(d) {
        fdate = d
    }

    // фон
    Rectangle {
        id: rectangle
        color: "#80ffffff"
        radius: 5
        anchors.fill: parent
    }

    // Row с двумя полями для текста
    Row {
        id: row
        anchors.fill: parent
        anchors.margins: 8

        Label {
            id: fileSize
            text: fsize
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
        }

        Label {
            id: fileDate
            text: fdate
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            anchors.rightMargin: 0
        }
    }
}


/*##^##
Designer {
    D{i:0;formeditorZoom:2}D{i:1}D{i:2}
}
##^##*/
