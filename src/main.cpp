#include <string>
#include <tgbot/bot.h>
#include <tgbot/methods/api.h>
#include <tgbot/methods/types.h>
#include <Tufao/HttpServer>
#include <Tufao/HttpServerRequest>
#include <Tufao/HttpServerRequestRouter>
#include <Tufao/Headers>
#include <QCoreApplication>
#include <QRegularExpression>
#include "telegrambot.h"
#include "database.h"
#include "vkmanager.h"
#include <src/json.hpp>
#include <iostream>
#include <cstdlib>
using namespace tgbot;
using namespace methods;
using namespace utils;
using json=::nlohmann::json;
int main(int argc, char** argv) {

    QCoreApplication a(argc, argv);
    int port = 80;
    qDebug()<<argc;
    std::cout<<argc;
    if(argc>1)
    	port = std::atoi(argv[1]);
    Tufao::HttpServer server;
    TelegramBot h(std::string("1335356640:AAEd3ZJ16EceNkXx46PgNM9q8Gd7vchgsxk"));
    QObject::connect(&server, &Tufao::HttpServer::requestReady,
                         &h, &TelegramBot::handleRequest);
    qDebug()<<"HELLO FROM DOCKER";
    std::cout<<"HELLO FROM DOCKER";
    server.listen(QHostAddress("0.0.0.0"), 8080);
    return a.exec();

}
