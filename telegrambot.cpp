#include "telegrambot.h"
#include <QJsonDocument>
#include <QUrl>
#include <QVariantMap>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>
#include <Tufao/HttpServerRequest>
#include <Tufao/Headers>
#include <tgbot/bot.h>
#include <tgbot/methods/api.h>
#include <tgbot/methods/types.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <json/json.h>

TelegramBot::TelegramBot(std::string token, QObject *parent) :
    QObject(parent)
{
    this->api = new Api(token);
    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(managerFinished(QNetworkReply*)));

}

TelegramBot::~TelegramBot()
{
    delete this->api;
}

void TelegramBot::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QByteArray answer = reply->readAll();
    std::string json = answer.toStdString();
    JSONCPP_STRING err;
    Json::Value root;
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(json.c_str(), json.c_str() + json.length(), &root,
            &err)){
        return;
    }
    if(json.find("access_token")){
        const std::string a_t = root["access_token"].asString();
        qDebug() << QString::fromStdString(a_t);
    }
    else if (json.find("response")) {
        qDebug() << "wall";
    }

}

bool TelegramBot::handleRequest(Tufao::HttpServerRequest &request,
                                Tufao::HttpServerResponse &response)
{
    if(request.url().toString() == "/"){
        QByteArray body = request.readBody();
        std::string bodyToStr = body.toStdString();
        JSONCPP_STRING err;
        Json::Value root;
        Json::CharReaderBuilder builder;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(bodyToStr.c_str(), bodyToStr.c_str() + bodyToStr.length(), &root,
                &err)){
            return false;
        }
         std::string id = root["message"]["chat"]["id"].asString();
         std::string text = root["message"]["text"].asString();
         if (text == "/start"){
             this->api->sendMessage(id, "https://oauth.vk.com/authorize?client_id=7533881&display=page&redirect_uri=http://a72dec838fc2.ngrok.io&scope=friends,wall&response_type=code&v=5.120");
         }
         else if (text == "/get"){
             this->api->sendMessage(id, "news");

         }

    }
    QStringList list = request.url().toString().split("=", QString::SkipEmptyParts);
    QString s = list.at(list.size()-1);
    this->request.setUrl("https://oauth.vk.com/access_token?client_id=7533881&client_secret=00YyZZO3rpJLkgzh0MpB&redirect_uri=http://a72dec838fc2.ngrok.io&code="+s);
    this->reply = this->manager->get(this->request);
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


