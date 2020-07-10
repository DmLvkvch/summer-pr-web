#include "telegrambot.h"
#include <QJsonDocument>
#include <QUrl>
#include <QVariantMap>
#include <QDebug>
#include <Tufao/HttpServerRequest>
#include <Tufao/Headers>
#include <tgbot/bot.h>
#include <tgbot/methods/api.h>
#include <tgbot/methods/types.h>
#include <QJsonObject>
#include <QDateTime>
#include <QNetworkReply>

TelegramBot::TelegramBot(std::string token, QObject *parent) : QObject(parent)
{
    this->api = new Api(token);
    manager = new QNetworkAccessManager();
}

TelegramBot::~TelegramBot()
{
    delete this->api;
}

void TelegramBot::managerFinished(QNetworkReply *reply, std::string id) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    QString answer = reply->readAll();
    qDebug()<<answer;
    QJsonDocument doc = QJsonDocument::fromJson(answer.toUtf8());
    QVariantMap msg = doc.object().toVariantMap();
    std::string token = msg["access_token"].toString().toStdString();
    std::cout<<token;
    //return token;
    VkManager vk(token);
    users.insert(QString::fromStdString(id), vk);
    std::cout<<id<<" "<<token;
}

void sendMultiMedia(std::string id, QList<QString> multimedia)
{

}

std::string TelegramBot::getChatId(QVariantMap msg)
{
    return ((msg["message"].toMap())["chat"].toMap())["id"].toString().toStdString();
}

std::string TelegramBot::getTelegramMessage(QVariantMap msg)
{
    return (msg["message"].toMap())["text"].toString().toStdString();
}

std::string TelegramBot::getUserId(QVariantMap msg)
{
    return ((msg["message"].toMap())["from"].toMap())["id"].toString().toStdString();
}

void TelegramBot::auth(std::string id)
{
    QObject::connect(manager, &QNetworkAccessManager::finished,
    [=](QNetworkReply* r)
        {
            managerFinished(r, id);
        });
        this->api->sendMessage(id, "https://oauth.vk.com/authorize?client_id=7532475&display=page&redirect_uri="
                                   "https://556af7a0e8bb.ngrok.io&scope=friends%2Cwall%2Cgroups%2Coffline&response_type=code&v=5.52");
}

void TelegramBot::onAuth(QUrl url)
{
    QStringList list = url.toString().split("=", QString::SkipEmptyParts);
    QString s = list.at(list.size()-1);
    this->request.setUrl("https://oauth.vk.com/access_token?client_id=7532475&client_secret=wsQzpMeHSVGmubpSX2no&redirect_uri=https://556af7a0e8bb.ngrok.io&code="+s);
    this->reply = this->manager->get(this->request);
}

void TelegramBot::onMessageReceived(QVariantMap msg)
{
    std::string from = this->getUserId(msg);
    std::string message = this->getTelegramMessage(msg);
    std::string chat = this->getChatId(msg);
    if(message=="/start")
    {
//            QStringList list = request.url().toString().split("=", QString::SkipEmptyParts);
//            QString s = list.at(list.size()-1);
//            this->request.setUrl("https://oauth.vk.com/access_token?client_id=7532475&client_secret=wsQzpMeHSVGmubpSX2no&redirect_uri=https://556af7a0e8bb.ngrok.io&code="+s);
//            this->reply = this->manager->get(this->request);
        auth(from);

    }
//    emit messageReceived(from, message, chat);
    if(message=="get"){
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            qDebug()<<it.key()<<" "<<QString::fromStdString(it.value().getToken());
        }
        VkManager vk = users.value(QString::fromStdString(chat));
        QList<VkPost> list = vk.getWall();
        b.add(from, list);
        for(VkPost post:list)
        {
            QDateTime date;
            date.setTime_t(post.getDate());
            QString time = date.toString(Qt::SystemLocaleShortDate);
            std::string message = post.getOwner()+"\n"+post.getText()+"\n"+time.toStdString();
            QList<QString> l = post.getPhotos();
            for(QString p:l)
            {
                message+=p.toStdString()+"\n";
            }
            this->api->sendMessage(chat, message);
        }
    }
}

bool TelegramBot::handleRequest(Tufao::HttpServerRequest &request,
                                Tufao::HttpServerResponse &response)
{
    QByteArray requestBody = request.readBody();
    QJsonDocument doc = QJsonDocument::fromJson(requestBody);
    QVariantMap msg = doc.object().toVariantMap();
//    std::string chat_id = getChatId(msg);
//    std::string message_text = getTelegramMessage(msg);
//    this->api->sendMessage(chat_id, message_text);
    qDebug()<<request.url().toString();
    if(request.url().toString().contains("?code=")){
        onAuth(request.url());
    }
    else
        onMessageReceived(msg);
    response.writeHead(Tufao::HttpResponseStatus::OK);
    response.headers().replace("Content-Type", "text/html; charset=utf-8");
    response << "<html><head><title>Request dumper</title></head><body>"
                "<p>Method: " << request.method() << "</p><p>Path: "
             << request.url().toString().toUtf8() << "</p><p>Version: HTTP/1."
             << (request.httpVersion() == Tufao::HttpVersion::HTTP_1_1
                 ? "1" : "0")
             << "</p><p>Headers:</p><ul>";

    {
        Tufao::Headers headers = request.headers();
        for (Tufao::Headers::const_iterator i = headers.begin()
             ;i != headers.end();++i) {
            response << "<li>" << i.key() << ": " << i.value();
        }
    }
    response << "</ul><p>Args:</p><ul>";

    QStringList args = request.customData().toMap()["args"].toStringList();
    for (int i = 0;i != args.size();++i) {
        response << "<li>" << args[i].toUtf8();
    }
    response.end("</ul></body></html>");
    return true;
}
