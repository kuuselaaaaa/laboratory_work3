#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QDir>
#include <QDirIterator>
#include <QList>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QDateTime>
#include <QLocale>
#include <QDesktopServices>
#include <QUrl>
#include <QMimeType>
#include <QMimeDatabase>

enum class ContentType
{
    DIR,
    FILE,
    UNKNOWN
};

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);
    QList<QString> getDirContent(QString path); // получает список файлов в папке

private:
    QString currentPath;                        // путь к текущей папке
    QHash<QString, QFileInfo> currentContent;   // информация о файлах в текщей папке
    void readContentInfo();                     // читает информацию о файлах в текущей папке
    QLocale locale;                             // локаль системы для форматирования строк

public slots:
    void requestUpdate();                       // запрос на обновление данных (из QML)
    bool isFile(QString path);                  // проверка на файл (любого типа)
    bool isDir(QString path);                   // проверка на папку
    QString getMimeName(QString path);          // получения информации о формате файла
    bool isAudioFile(QString path);             // провека на аудио-файл
    bool isVideoFile(QString path);             // провека на видео-файл
    bool isCodeFile(QString path);              // провека на файл исходного кода
    bool isImageFile(QString path);             // проверка на файл-изображение
    QString getFileName(QString path);          // получение имени по пути
    QString getFileSize(QString path);          // получение размера файла
    QString getFileModTime(QString path);       // получание фремени модификации файла
    bool setPath(QString newPath);              // установка текущего пути
    bool openFile(QString path);                // открытие файла приложением по умолчанию

signals:
    void updateModel(QList<QString> paths);     // сигнал на обновление информации в QML

};

#endif // UTILS_H
