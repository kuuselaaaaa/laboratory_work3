#include "utils.h"
#include <iostream>

Utils::Utils(QObject *parent) : QObject(parent)
{
    locale = QLocale::system();
    setPath(QDir::currentPath()); // устанавливаем текущую директорию

    readContentInfo();
}

/*
 * В этой функции можно было использовать QDitIterator, но тогда не получится сортировать файлы
 * (QDir::SortFlag::DirsFirst | QDir::SortFlag::Name)
 */
QList<QString> Utils::getDirContent(QString path) {
    // получаем список имен файлов и папок в path
    QDir dir(path);
    QStringList list = dir.entryList(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::Hidden | QDir::NoDotAndDotDot, QDir::SortFlag::DirsFirst | QDir::SortFlag::Name);

    // обходим список и получаем абсолютные пути (от рута)
    QList<QString> content;
    foreach(QString entry, list) {
        content.push_back(dir.absoluteFilePath(entry));
    }

    return content;
}

bool Utils::setPath(QString newPath) {
    QFileInfo pathInfo(newPath); // получаем информацию о файле или папке

    // проверям что путь существует и что это папка
    if(!pathInfo.exists() || !pathInfo.isDir()) {
        return false; // невалидный путь к папке
    }

    // ставим рабочую папку по указаному пути
    currentPath = pathInfo.absoluteFilePath();
    QDir::setCurrent(currentPath);

    // читаем содержимое папки
    readContentInfo();
    return true;
}

void Utils::readContentInfo() {
    QList<QString> content = getDirContent(currentPath); // получаем список путей

    currentContent.clear(); // очищаем текущий список

    // получаем информацию о файлах и добавляем её в список
    foreach(QString entry, content) {
        QFileInfo info(entry);
        currentContent[info.absoluteFilePath()] = info;
    }

    // обновляем QML
    emit updateModel(content);
}

bool Utils::isDir(QString path) {
    if(!currentContent.contains(path)) return false;
    return currentContent[path].isDir();
}

bool Utils::isFile(QString path) {
    if(!currentContent.contains(path)) return false;
    return currentContent[path].isFile();
}

QString Utils::getMimeName(QString path) {
    QMimeDatabase db;
    QMimeType fileType = db.mimeTypeForFile(path, QMimeDatabase::MatchExtension);
    return fileType.name();
}

bool Utils::isAudioFile(QString path) {
    return getMimeName(path).startsWith("audio");
}

bool Utils::isVideoFile(QString path) {
    return getMimeName(path).startsWith("video");
}

bool Utils::isImageFile(QString path) {
    return getMimeName(path).startsWith("image");
}

bool Utils::isCodeFile(QString path) {
    // с text/x начинаются файлы с исходным кодом
    return getMimeName(path).startsWith("text/x");
}

QString Utils::getFileName(QString path) {
    if(!currentContent.contains(path)) return QString("???");
    return currentContent[path].fileName();
}

QString Utils::getFileSize(QString path) {
    if(!currentContent.contains(path)) return QString("???");
    return locale.formattedDataSize(currentContent[path].size());
}

QString Utils::getFileModTime(QString path) {
    if(!currentContent.contains(path)) return QString("???");
    return currentContent[path].lastModified().toString("h:m:s - dd/mm/yyyy");
}

void Utils::requestUpdate() {
    // получеам пути и обновляем QML
    QList<QString> paths = currentContent.keys();
    emit updateModel(paths);
}

bool Utils::openFile(QString path) {
    // открываем файл приложением по умолчанию
    return QDesktopServices::openUrl(QUrl("file://" + path));
}
