#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <QNetworkAccessManager>
#include <QObject>
#include <Tufao/AbstractHttpServerRequestHandler>
#include <tgbot/bot.h>
#include <tgbot/methods/api.h>
#include <tgbot/methods/types.h>
#include <QNetworkRequest>
using namespace tgbot;
using namespace types;
using namespace methods;
using namespace utils;

class TelegramBot : public QObject,
        public Tufao::AbstractHttpServerRequestHandler
{
    Q_OBJECT
public:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    explicit TelegramBot(std::string api, QObject *parent = 0);
    void GET();
    ~TelegramBot();
public slots:
    bool handleRequest(Tufao::HttpServerRequest &request,
           Tufao::HttpServerResponse &response) override;
    private slots:
        void managerFinished(QNetworkReply *reply);
private:
    Api* api;
    QNetworkReply* reply;
};
#endif // TELEGRAMBOT_H
