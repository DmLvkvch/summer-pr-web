#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <QNetworkAccessManager>
#include <string>
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
#include <QHash>
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
    void onTgMessageReceived(QVariantMap message);
    void auth(std::string id);
    void sendMultiMedia(std::string id, QList<QString> multimedia);
    void parseCode(QUrl url);
    void checkTime(std::string chat);
signals:
    void messageReceived(std::string, std::string, std::string);
public slots:
    bool handleRequest(Tufao::HttpServerRequest &request,
                       Tufao::HttpServerResponse &response) override;
    void managerFinished(QNetworkReply *reply, std::string id);
private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QNetworkReply* reply;
    std::string getTelegramMessage(QVariantMap message);
    std::string getChatId(QVariantMap message);
    Api* api;
    QHash<QString, VkManager> users;
    DataBase* b;
};
#endif // TELEGRAMBOT_H
