#ifndef DATABASE_H
#define DATABASE_H

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/logger.hpp>

#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <QJsonDocument>
#include<QJsonObject>
#include <QString>
#include <QVariantMap>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

class DataBase
{
public:
    DataBase();
    void createRecord(std::string id, std::string time);
    void updateTime(std::string id, std::string new_time);
    std::string getTime(std::string id);
};


#endif // DATABASE_H
