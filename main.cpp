#include <string>
#include <tgbot/bot.h>
#include <tgbot/methods/api.h>
#include <tgbot/methods/types.h>
#include <iostream>
#include <Tufao/HttpServer>
#include <Tufao/HttpServerRequest>
#include <Tufao/HttpServerRequestRouter>
#include <Tufao/Headers>
#include <QUrl>
#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include "telegrambot.h"

using namespace tgbot;
using namespace methods;
using namespace utils;




int main(int argc, char** argv) {
    QCoreApplication a(argc, argv);
    Tufao::HttpServer server;
    TelegramBot h(std::string("1330433063:AAHcgyYjCM5eb-4jUlpkhXGCMt5uIfZJkg4"));
    QObject::connect(&server, &Tufao::HttpServer::requestReady,
                         &h, &TelegramBot::handleRequest);

    server.listen(QHostAddress("127.0.0.1"), 8080);
    return a.exec();

}
