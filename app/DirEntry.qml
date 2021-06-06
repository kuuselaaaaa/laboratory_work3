import QtQuick 2.12
import QtQuick.Controls 2.12


Item {
    id: entryItem
    height: 80
    width: 80

    // информация о файле
    property string filePathStr: ""
    property string fileNameStr: ""
    property string fileSizeStr: ""
    property string fileDateStr: ""
    property string fileIconPath: "images/unknown.svg"

    // индекс объекта в GridView
    property int selfIndex: index

    // выбран ли объект
    property bool selected: false

    // иконка файла
    Image {
        id: image
        anchors.fill: parent
        source: fileIconPath
        anchors.rightMargin: 8
        anchors.leftMargin: 8
        anchors.bottomMargin: 8
        anchors.topMargin: 8
    }

    // фон для текста
    Rectangle {
        id: rectangle
        color: "#80ffffff"
        anchors.fill: label
        radius: 5
    }

    // имя файла
    Label {
        id: label
        text: fileNameStr
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: image.bottom
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: selected ? Text.Wrap : Text.NoWrap
        clip: true
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.rightMargin: 0
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:6}D{i:1}
}
##^##*/
