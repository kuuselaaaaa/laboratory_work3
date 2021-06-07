#ifndef UTILSTEST_H
#define UTILSTEST_H

#include <gtest/gtest.h>
#include <QDir>
#include <iostream>
#include <QFileInfo>

#include "../app/utils.h"

TEST(dircontent, noempty)
{
    QDir dir(".");

    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");
    QList<QString> info;
    QString file_name;


    for (int i = 0; i < 10; i++) {
        file_name = "./test_dir/testfile_" + QString::number(i) + ".txt";
        QFile file(file_name);
        file.open(QIODevice::WriteOnly);
        QFileInfo infofile(file_name);
        info.push_back(infofile.absoluteFilePath());
    }

    Utils utils;

    QList<QString> res = utils.getDirContent("./test_dir");
    for (int i = 0; i < res.length(); i++){
        EXPECT_TRUE(res.contains(info[i]));
    }

    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(dircontent, large_dir)
{
    QDir dir(".");

    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");
    QList<QString> info;
    QString file_name;

    for (int i = 0; i < 1000; i++) {
        file_name = "./test_dir/testfile_" + QString::number(i) + ".txt";
        QFile file(file_name);
        file.open(QIODevice::WriteOnly);
        QFileInfo infofile(file_name);
        info.push_back(infofile.absoluteFilePath());
    }

    Utils utils;

    QList<QString> res = utils.getDirContent("./test_dir");
    for (int i = 0; i < res.length(); i++){
        EXPECT_TRUE(res.contains(info[i]));
    }

    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(dircontent, empty)
{
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    Utils utils;

    QList<QString> res = utils.getDirContent("./test_dir");

    EXPECT_TRUE(res.isEmpty());

    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(setpath, noempty)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");
    dir.cd("test_dir");
    dir.mkdir("test_subdir");

    QFileInfo info("./test_dir/test_subdir");

    Utils utils;

    bool res = utils.setPath(info.absoluteFilePath());

    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(setpath, isfile)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");
    QString file_name = "./test_dir/testfile.txt";
    QFile file(file_name);
    file.open(QIODevice::WriteOnly);

    QFileInfo info(file_name);

    Utils utils;

    bool res = utils.setPath(info.absoluteFilePath());
    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(setpath, empty)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QFileInfo info("./test_dir/test_subdir");

    Utils utils;

    bool res = utils.setPath(info.absoluteFilePath());

    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isdir, dir)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");

    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QFileInfo info("test_dir");

    Utils utils;
    bool res = utils.isDir(info.absoluteFilePath());

    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isdir, file)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.txt";
    QFile file(file_name);
    file.open(QIODevice::WriteOnly);

    QFileInfo info("./test_dir/testfile.txt");

    Utils utils;
    utils.setPath(info.absolutePath());
    bool res = utils.isDir(info.absoluteFilePath());

    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isdir, not_exists)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QFileInfo info("./test_dir/testfile.txt");

    Utils utils;
    utils.setPath(info.absolutePath());
    bool res = utils.isDir(info.absoluteFilePath());

    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isfile, file)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.txt";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    utils.setPath(info.absolutePath());
    bool res = utils.isFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isfile, dir)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QFileInfo info("./test_dir");

    Utils utils;
    utils.setPath(info.absolutePath());
    bool res = utils.isFile(info.absoluteFilePath());

    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isfile, not_exists)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QFileInfo info("./test_dir/testfile.txt");

    Utils utils;
    utils.setPath(info.absolutePath());
    bool res = utils.isFile(info.absoluteFilePath());

    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isaudio, audio)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.mp3";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isAudioFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isaudio, notaudio)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.mp4";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isAudioFile(info.absoluteFilePath());
    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isvideo, video)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.mp4";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isVideoFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isvideo, videomkv)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.mkv";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isVideoFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isvideo, notvideo)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.mp3";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isVideoFile(info.absoluteFilePath());
    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isimage, imagepng)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.png";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isImageFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isimage, imagejpg)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.jpg";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isImageFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isimage, imagejpeg)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.jpeg";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isImageFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isimage, imagebmp)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.bmp";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isImageFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(isimage, notimage)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.mp3";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isImageFile(info.absoluteFilePath());
    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(iscode, codec)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.c";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isCodeFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(iscode, codecpp)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.cpp";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isCodeFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(iscode, codepy)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.py";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isCodeFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(iscode, codecs)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.cs";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isCodeFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(iscode, codeh)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.h";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isCodeFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(iscode, codehpp)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.hpp";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isCodeFile(info.absoluteFilePath());
    EXPECT_TRUE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(iscode, notcode)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.png";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    bool res = utils.isCodeFile(info.absoluteFilePath());
    EXPECT_FALSE(res);

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(getname, exists)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.png";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    utils.setPath(info.absolutePath());
    QString res = utils.getFileName(info.absoluteFilePath());
    EXPECT_STREQ(res.toStdString().c_str(), "testfile.png");

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(getname, notexists)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.png";

    QFileInfo info(file_name);

    Utils utils;
    utils.setPath(info.absolutePath());
    QString res = utils.getFileName(info.absoluteFilePath());
    EXPECT_STREQ(res.toStdString().c_str(), "???");

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(getsize, exists)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.png";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);

    Utils utils;
    utils.setPath(info.absolutePath());
    QString res = utils.getFileSize(info.absoluteFilePath());
    EXPECT_STREQ(res.toStdString().c_str(), "0 bytes");

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(getsize, notempty)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.txt";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);
    QString str = "Hello world";
    file.write(str.toUtf8());
    file.close();

    QFileInfo info(file_name);

    Utils utils;
    utils.setPath(info.absolutePath());
    QString res = utils.getFileSize(info.absoluteFilePath());
    EXPECT_STREQ(res.toStdString().c_str(), "11 bytes");

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(getsize, notexists)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.txt";
    QFileInfo info(file_name);

    Utils utils;
    utils.setPath(info.absolutePath());
    QString res = utils.getFileSize(info.absoluteFilePath());
    EXPECT_STREQ(res.toStdString().c_str(), "???");

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(getfilemodtime, exists)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.png";
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);

    QFileInfo info(file_name);
    QString last_mod = info.lastModified().toString("h:m:s - dd/mm/yyyy");

    Utils utils;
    utils.setPath(info.absolutePath());
    QString res = utils.getFileModTime(info.absoluteFilePath());
    EXPECT_STREQ(res.toStdString().c_str(), last_mod.toStdString().c_str());

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(getfilemodtime, notexists)
{
    QString pathBackup = QDir::currentPath();
    QDir dir(".");
    if(dir.exists("test_dir")) {
        dir.cd("test_dir");
        dir.removeRecursively();
    }

    dir.mkdir("test_dir");

    QString file_name = "./test_dir/testfile.png";
    QFileInfo info(file_name);

    Utils utils;
    utils.setPath(info.absolutePath());
    QString res = utils.getFileModTime(info.absoluteFilePath());
    EXPECT_STREQ(res.toStdString().c_str(), "???");

    QDir::setCurrent(pathBackup);
    dir.cd(pathBackup);
    dir.cd("test_dir");
    dir.removeRecursively();
}

#endif // UTILSTEST_H
