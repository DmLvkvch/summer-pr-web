#ifndef DATABASE_H
#define DATABASE_H

#include <chrono>

#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/options/find.hpp>
#include <iostream>
#include <QObject>
#include "vkpost.h"
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

class Database : public QObject
{
    Q_OBJECT
public:
    Database();
    void add(std::string user_id, QList<VkPost>);
    void add(std::string user_id, VkPost vk);
    bsoncxx::document::value createDocument(std::string id, VkPost post);
private:
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};
    mongocxx::database db;

};

#endif // DATABASE_H
