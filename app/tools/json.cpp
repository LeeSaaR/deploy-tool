#include "json.h"


const QString Json::extractString(const QString &key, QJsonObject &obj)
{
    return obj.find(key).value().toString();
}

const int Json::extractInt(const QString &key, QJsonObject &obj)
{
    return obj.find(key).value().toInt();
}

const double Json::extractDouble(const QString &key, QJsonObject &obj)
{
    return obj.find(key).value().toDouble();
}

const bool Json::extractBool(const QString &key, QJsonObject &obj)
{
    return obj.find(key).value().toBool();
}
