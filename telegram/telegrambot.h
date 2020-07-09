#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <QNetworkAccessManager>
#include <QObject>
#include <Tufao/AbstractHttpServerRequestHandler>
#include <tgbot/bot.h>
#include <tgbot/methods/api.h>
#include <tgbot/methods/types.h>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "database.h"
#include "vkmanager.h"
#include "vkpost.h"
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
    std::string getUserId(QVariantMap msg);
    void onMessageReceived(QVariantMap message);
signals:
    void messageReceived(std::string, std::string, std::string);
public slots:
    bool handleRequest(Tufao::HttpServerRequest &request,
                       Tufao::HttpServerResponse &response) override;
    void managerFinished(QNetworkReply *reply);
private:
    Database b;
    VkManager vk;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QNetworkReply* reply;
    std::string getTelegramMessage(QVariantMap message);
    std::string getChatId(QVariantMap message);
    Api* api;
    std::string token;
};
#endif // TELEGRAMBOT_H
