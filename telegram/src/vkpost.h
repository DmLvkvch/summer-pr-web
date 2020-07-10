#ifndef VKPOST_H
#define VKPOST_H

#include <string>
#include <QObject>
#include <QList>
#include <QString>
class VkPost : public QObject
{
    Q_OBJECT
public:
    VkPost(long long date, std::string text, long long source, std::string owner);
    VkPost(const VkPost&);
    VkPost& operator=(const VkPost& vk);
    std::string getOwner() const;
    void setOwner(const std::string &value);

    std::string getText() const;
    void setText(const std::string &value);

    long long getSource() const;
    void setSource(long long value);

    long long getDate() const;
    void setDate(long long value);

    QList<QString> getPhotos() const;
    void setPhotos(const QList<QString> &value);

private:
    std::string owner;
    std::string text;
    long long source;
    long long date;
    QList<QString> photos;

};

#endif // VKPOST_H
