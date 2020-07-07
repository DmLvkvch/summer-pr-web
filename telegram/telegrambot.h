#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <QObject>
#include <Tufao/AbstractHttpServerRequestHandler>
#include <tgbot/bot.h>
#include <tgbot/methods/api.h>
#include <tgbot/methods/types.h>
using namespace tgbot;
using namespace types;
using namespace methods;
using namespace utils;

class TelegramBot : public QObject,
        public Tufao::AbstractHttpServerRequestHandler
{
    Q_OBJECT
public:
    explicit TelegramBot(std::string api, QObject *parent = 0);
    ~TelegramBot();
public slots:
    bool handleRequest(Tufao::HttpServerRequest &request,
           Tufao::HttpServerResponse &response) override;
private:
    Api* api;
};
#endif // TELEGRAMBOT_H
