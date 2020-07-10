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
    delete manager;
}

void TelegramBot::managerFinished(QNetworkReply *reply, std::string id) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    QString answer = reply->readAll();
    qDebug()<<QString::fromStdString(id)<<" "<<answer;
    if(answer=="" || !answer.contains("access_token"))
        return;
    QJsonDocument doc = QJsonDocument::fromJson(answer.toUtf8());
    QVariantMap msg = doc.object().toVariantMap();
    std::string token = msg["access_token"].toString().toStdString();
    VkManager vk(token);
    users.insert(QString::fromStdString(id), vk);
    this->api->sendMessage(id, "Hello");
    delete manager;
    manager = new QNetworkAccessManager();
    //QObje
}

void TelegramBot::sendMultiMedia(std::string id, QList<QString> multimedia)
{
    std::string query = "https://api.telegram.org/bot1335356640:AAEd3ZJ16EceNkXx46PgNM9q8Gd7vchgsxk/sendMediaGroup?";
    std::string chat_id = "chat_id="+id;
    std::string media = "media=[";
    for(QString tmp : multimedia)
    {
        media+="{\"type\":\"photo\",\"media\":\""+tmp.toStdString()+"\"},";
    }
    media = media.substr(0, media.length()-1);
    media+="]";
    query+=chat_id+"&"+media;
    std::cout<<query<<std::endl;
    this->request.setUrl(QString::fromStdString(query));
    this->reply = this->manager->get(this->request);
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
                     [=](QNetworkReply* reply){
        managerFinished(reply, id);
    });
    this->api->sendMessage(id, "https://oauth.vk.com/authorize?client_id=7532475&display=page&redirect_uri="
                               "https://556af7a0e8bb.ngrok.io&scope=friends%2Cwall%2Cgroups%2Coffline&response_type=code&v=5.52");
}

void TelegramBot::parseCode(QUrl url)
{
    QStringList list = url.toString().split("=", QString::SkipEmptyParts);
    QString code = list.at(list.size()-1);
    this->request.setUrl("https://oauth.vk.com/access_token?client_id=7532475&client_secret=wsQzpMeHSVGmubpSX2no&redirect_uri=https://556af7a0e8bb.ngrok.io&code="+code);
    this->reply = this->manager->get(this->request);
}

void TelegramBot::onTgMessageReceived(QVariantMap msg)
{
    std::string from = this->getUserId(msg);
    std::string message = this->getTelegramMessage(msg);
    std::string chat = this->getChatId(msg);
    if(message=="/start")
    {
        auth(chat);
    }
    else if(message=="/get"){
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            qDebug()<<it.key()<<" --- "<<QString::fromStdString(it.value().getToken());
        }
        VkManager vk = users.value(QString::fromStdString(chat));
        QList<VkPost> list = vk.getWall();
        for(VkPost post:list)
        {
            QDateTime date;
            date.setTime_t(post.getDate());
            QString time = date.toString(Qt::SystemLocaleShortDate);
            QDateTime t = QDateTime::fromTime_t(post.getDate());
            std::string message = post.getOwner()+"\n"+post.getText()+"\n"+t.toString().toStdString();
            QList<QString> l = post.getPhotos();
            this->api->sendMessage(chat, message);
            if(l.size()>1)
            {
                sendMultiMedia(chat, l);
            }
            else if(l.size()==1)
                api->sendPhoto(chat, l[0].toStdString());
        }
    }
}

bool TelegramBot::handleRequest(Tufao::HttpServerRequest &request,
                                Tufao::HttpServerResponse &response)
{
    QByteArray requestBody = request.readBody();
    QJsonDocument doc = QJsonDocument::fromJson(requestBody);
    QVariantMap msg = doc.object().toVariantMap();
    if(request.url().toString().contains("?code=")){
        parseCode(request.url());
    }
    else {
        onTgMessageReceived(msg);
    }
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
