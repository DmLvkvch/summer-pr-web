#include "vkmanager.h"
#include "src/api.h"
#include"src/json.hpp"
#include <string>
#include <iostream>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonDocument>
#include <QDebug>
#include "vkpost.h"

using json=::nlohmann::json;

VkManager::VkManager(std::string token)
{
    this->token = token;
}

VkManager::VkManager()
{

    api.auth("", "", "3498e4d5ccb8836cfee69075b28e1bfbb67188670b172456bbefe44db4645c264ab7cd7dab79c0868f140");
}


QList<VkPost> VkManager::getWall()
{
    QList<VkPost> list;

    json data;
    data = api.call("wall.get");
    std::string str = data.dump();
    QString js = QString::fromStdString(str);
    QJsonDocument doc = QJsonDocument::fromJson(js.toUtf8());
    QVariantMap msg = doc.object().toVariantMap();
    QVariantList posts = (msg["response"].toMap())["items"].toList();
    QVariantList groups = (msg["response"].toMap())["groups"].toList();
    for(QVariant tmp : posts)
    {
        QVariantMap post = tmp.toMap();
        long long date = post["date"].toLongLong();
        std::string text = post["text"].toString().toStdString();
        long long source = post["from_id"].toLongLong();
        QList<QString> photos;
        if(post["attachments"].toList().size()>0)
        {
            QVariantList attachs = post["attachments"].toList();
            for(QVariant attach:attachs)
            {
                QVariantMap tmp = attach.toMap();
                if(tmp["type"].toString()=="photo")
                {
                    photos.push_back((tmp["photo"].toMap())["photo_130"].toString());
                }
            }
        }
        std::string name;
        for(QVariant group : groups)
        {
            QVariantMap group_tmp = group.toMap();
            if(group_tmp["id"].toLongLong()==source || group_tmp["id"].toLongLong()== -source)
            {
                name = group_tmp["name"].toString().toStdString();
                break;
            }
        }
        VkPost vkPost(date, text, source, name);
        vkPost.setPhotos(photos);
        list.push_back(vkPost);
        std::cout<<date<<text<<source<<name<<std::endl;
    }
    return list;
}

void VkManager::handle()
{

}

std::string VkManager::getToken() const
{
    return token;
}

void VkManager::setToken(const std::string &value)
{
    token = value;
}
