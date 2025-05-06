#include "io.h"

#include <QDebug>
#include <QFile>
#include <QDir>

void IO::deleteDir(const QString &dir_path)
{
    qDebug() << __FUNCTION__;
    QDir dir(dir_path);
    dir.removeRecursively();
}

void IO::makeDir(const QString &dir_path)
{
    qDebug() << __FUNCTION__;
    if (QFile::exists(dir_path)) return;

    QDir dir;
    dir.mkdir(dir_path);
}

const QString IO::readFile(const QString &file_name)
{
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    const QString content = file.readAll();
    file.close();
    return content;
}

const QStringList IO::listFiles(const QString &dir_path)
{
    QStringList out;
    QDir dir(dir_path);
    out = dir.entryList();
    out.removeOne(".");
    out.removeOne("..");
    return out;
}

const void IO::copyFile(const QString &file_path, QString dir_path, const QString &new_name)
{
    if (new_name.isEmpty())
    {
        const QString fileName = QFileInfo(file_path).fileName();
        QFile::copy(file_path, dir_path+"/"+fileName);
    }
    else
    {
        QFile::copy(file_path, dir_path+"/"+new_name);
    }
}

const void IO::writeFile(const QString& content, const QString &file_path)
{
    //if (QFile::exists(file_path)) return;

    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    in << content;
    file.flush();
    file.close();
}

