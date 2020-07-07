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
#include <QJsonDocument>
#include <QJsonObject>
TelegramBot::TelegramBot(std::string token, QObject *parent) :
    QObject(parent)
{
    this->api = new Api(token);
}

TelegramBot::~TelegramBot()
{
    delete this->api;
}

bool TelegramBot::handleRequest(Tufao::HttpServerRequest &request,
                                Tufao::HttpServerResponse &response)
{

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
    QByteArray requestBody = request.readBody();
    response << "</ul><p>Args:</p><ul>";
    QJsonDocument doc = QJsonDocument::fromJson(requestBody);
    QVariantMap msg = doc.object().toVariantMap();
    qDebug()<<requestBody;
    this->api->sendMessage("176262121.0", "khfiuwenhofweo");
    //api.sendMessage()
    response.end("</ul></body></html>");
    return true;
}
