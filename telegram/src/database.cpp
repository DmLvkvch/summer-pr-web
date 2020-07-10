#include "database.h"

#include <QDateTime>

Database::Database()
{
        db = conn["test"];
}

bsoncxx::document::value Database::createDocument(std::string id, VkPost post)
{
    QDateTime date;
    date.setTime_t(post.getDate());
    bsoncxx::document::value doc = make_document(kvp("user_id", id), kvp("owner", post.getOwner()), kvp("text", post.getText()), kvp("time", std::to_string(post.getDate())));
    return doc;
}

void Database::add(std::string user_id, QList<VkPost> vk)
{
    for(VkPost post : vk)
    {
        //this->add(user_id, vk);
    }
}

void Database::add(std::string user_id, VkPost vk)
{
    bsoncxx::document::value doc = createDocument(user_id, vk);
    auto res = db["posts"].insert_one(std::move(doc));
}
