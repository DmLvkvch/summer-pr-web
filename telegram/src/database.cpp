#include "database.h"
#include <iostream>

DataBase::DataBase()
{
    mongocxx::instance instance{};

}

void DataBase::createRecord(std::string id, std::string time){
    mongocxx::uri uri("mongodb://127.0.0.1:27017");
    mongocxx::client client(uri);
    mongocxx::database db = client["VK"];
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
            << "id" <<  id
            << "last_post" << time
       << bsoncxx::builder::stream::finalize;
    auto res = db["VK"].insert_one(std::move(doc_value));
}

void DataBase::updateTime(std::string id, std::string new_time){
    mongocxx::uri uri("mongodb://127.0.0.1:27017");
    mongocxx::client client(uri);
    mongocxx::database db = client["VK"];
    db["VK"].update_one(
                make_document(kvp("id", id)),
                make_document(kvp("$set", make_document(kvp("last_post", new_time)))));

}

std::string DataBase::getTime(std::string id){
    mongocxx::uri uri("mongodb://127.0.0.1:27017");
    mongocxx::client client(uri);
    mongocxx::database db = client["VK"];
    mongocxx::collection coll = db["VK"];
    bsoncxx::stdx::optional<bsoncxx::document::value> res =
            coll.find_one(bsoncxx::builder::stream::document{}
                        << "id" << id <<
                        bsoncxx::builder::stream::finalize);
    if (res){
        QString ans =  QString::fromStdString(bsoncxx::to_json(*res));
        QJsonDocument doc = QJsonDocument::fromJson(ans.toUtf8());
        QVariantMap msg = doc.object().toVariantMap();
        std::string time = msg["last_post"].toString().toStdString();
        std::cout << time <<std::endl;
        return time;
    }
    else{
        return "0";
    }

}

