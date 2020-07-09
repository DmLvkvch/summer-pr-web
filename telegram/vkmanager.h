#ifndef VKMANAGER_H
#define VKMANAGER_H

#include "src/api.h"
#include "src/json.hpp"
#include "vkpost.h"
#include <QObject>
using json=::nlohmann::json;
class VkManager : public QObject
{
    Q_OBJECT
public:
    VkManager(std::string token);
    VkManager();
    QList<VkPost> getWall();
    std::string getToken() const;
    void setToken(const std::string &value);

public slots:
    void handle();
private:
    std::string token;
    long long start_time = -1;
    VK::Client api;
};

#endif // VKMANAGER_H
