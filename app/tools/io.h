#ifndef IO_H
#define IO_H

#include <QString>

class IO
{
private:
    IO(){}
public:
    static void deleteDir(const QString& dir_path);
    static void makeDir(const QString& dir_path);
    static const QString readFile(const QString& file_name);
    static const QStringList listFiles(const QString& dir_path);
    static const void copyFile(const QString& file_path, QString dir_path, const QString& new_name = "");
    static const void writeFile(const QString &content, const QString& file_path);
};

#endif // IO_H
