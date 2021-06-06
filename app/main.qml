import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.2

// основной файл интерфейса
Window {
    id: window
    width: 640
    height: 480
    visible: true
    color: "#ffffff"
    title: qsTr("File manager")

    // фон приложения
    Image {
        id: bg
        opacity: 1
        source: "images/background.png"
        sourceSize.height: 250
        sourceSize.width: 250
        fillMode: Image.Tile // повторять картинку (бесконечный размер)
        anchors.fill: parent
    }

    // размытие фона
    FastBlur {
        anchors.fill: bg
        source: bg
        radius: 32
    }

    // нижняя панель
    BottomBar {
        id: bBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.bottomMargin: 8

    }

    // модель для хранения файлов и папок
    ListModel {
        id: dirContentModel
    }

    // отображение файлов и папок в виде сетки
    GridView {
        id: dirContent
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: bBar.top
        clip: true

        cellHeight: 120
        anchors.rightMargin: 16
        anchors.leftMargin: 16
        anchors.bottomMargin: 8
        anchors.topMargin: 16

        // модель с данными для отображения
        model: dirContentModel

        // шаблон объекта, который отображается
        delegate: DirEntry {
            id: entry
            fileNameStr: fileName
            fileSizeStr: fileSize
            fileDateStr: fileDate
            fileIconPath: fileIcon
            filePathStr: filePath

            selected: (dirContent.currentIndex == selfIndex)

            // обновляем панель, если объект выбран
            onSelectedChanged: {
                if(selected) {
                    bBar.setSize(fileSizeStr)
                    bBar.setDate(fileDateStr)
                }
            }

            // для выбора при помощи мыши
            MouseArea {
                anchors.fill: parent

                // обычное нажатие
                onClicked: {
                    dirContent.currentIndex = selfIndex
                }

                // двойное нажатие
                onDoubleClicked: {
                    if(entry.filePathStr === ".." || utils.isDir(filePathStr)) {
                        if(utils.setPath(filePathStr) === true) {
                            dirContent.positionViewAtBeginning()
                        } else {
                            errorDialog.text = "Невозомжно перейти в папку"
                            errorDialog.open()
                        }
                    } else if(utils.isFile(filePathStr)) {
                        if(utils.openFile(filePathStr) !== true) {
                            errorDialog.text = "Невозомжно открыть файл"
                            errorDialog.open()
                        }
                    } else {
                        errorDialog.text = "Неизвестный объект!"
                        errorDialog.open()
                    }
                }
            }
        }

        // фон выбранного объекта
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }

    // когда интерфейс загрузился, получаем данные первый раз
    Component.onCompleted: {
        utils.requestUpdate();
    }

    // обработка сигналов из C++
    Connections {
        target: utils

        onUpdateModel: {
            console.log("update")

            // очищаем список
            dirContentModel.clear()
            // добавляем объект для перехода в родительский каталог (.. в Linux и MacOS)
            dirContentModel.append({fileName: "..", filePath: "..", fileSize: "", fileDate: "", fileIcon: "images/folder.svg"})

            // добавляем остальные файлы (paths приходит из C++)
            for(var i in paths) {
                var path = paths[i]
                var name = utils.getFileName(path)
                var size = utils.getFileSize(path)
                var modTime = utils.getFileModTime(path)
                var icon = "images/unknown.svg"

                // ставим нужную иконку
                if(utils.isDir(path)) {
                    icon = "images/folder.svg"
                } else if(utils.isFile(path)) {
                    icon = "images/file.svg"

                    if(utils.isAudioFile(path)) {
                        icon = "images/music_file.svg"
                    } else if(utils.isVideoFile(path)) {
                        icon = "images/video_file.svg"
                    } else if(utils.isCodeFile(path)) {
                        icon = "images/code_file.svg"
                    } else if(utils.isImageFile(path)) {
                        icon = "images/image.svg"
                    }
                }

                // добавляем в модель
                dirContentModel.append({fileName: name, filePath: path, fileSize: size, fileDate: modTime, fileIcon: icon})
            }
        }
    }

    // диалог для отображения ошибки
    MessageDialog {
        id: errorDialog
        title: "Ошибка!"
        text: ""
        icon: StandardIcon.Critical
    }

}

