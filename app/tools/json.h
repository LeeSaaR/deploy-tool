#ifndef JSON_H
#define JSON_H

#include <QJsonObject>
#include <QString>

class Json
{
private:
    Json(){}
public:
    static const QString extractString(const QString& key, QJsonObject& obj);
    static const int extractInt(const QString& key, QJsonObject& obj);
    static const double extractDouble(const QString& key, QJsonObject& obj);
    static const bool extractBool(const QString& key, QJsonObject& obj);
};

#endif // JSON_H
