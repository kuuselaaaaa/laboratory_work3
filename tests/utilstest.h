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

    dir.removeRecursively();
}

TEST(setpath, isfile)
{
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

    dir.cd("test_dir");
    dir.removeRecursively();
}

TEST(setpath, empty)
{
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

    dir.cd("test_dir");
    dir.removeRecursively();
}

#endif // UTILSTEST_H
