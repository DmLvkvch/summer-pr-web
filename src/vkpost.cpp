#include "vkpost.h"

VkPost::VkPost(long long date, std::string text, long long source, std::string owner):QObject(nullptr)
{
    this->date = date;
    this->text = text;
    this->source = source;
    this->owner = owner;
}

VkPost::VkPost(const VkPost &vk):QObject(nullptr)
{
    this->date = vk.date;
    this->text = vk.text;
    this->source = vk.source;
    this->owner = vk.owner;
    this->photos=vk.photos;
}

VkPost &VkPost::operator=(const VkPost& vk)
{
    if(&vk==this)
        return *this;
    this->date = vk.date;
    this->text = vk.text;
    this->source = vk.source;
    this->owner = vk.owner;
    this->photos = vk.photos;
    return *this;
}

std::string VkPost::getOwner() const
{
    return owner;
}

void VkPost::setOwner(const std::string &value)
{
    owner = value;
}

std::string VkPost::getText() const
{
    return text;
}

void VkPost::setText(const std::string &value)
{
    text = value;
}

long long VkPost::getSource() const
{
    return source;
}

void VkPost::setSource(long long value)
{
    source = value;
}

long long VkPost::getDate() const
{
    return date;
}

void VkPost::setDate(long long value)
{
    date = value;
}

QList<QString> VkPost::getPhotos() const
{
    return photos;
}

void VkPost::setPhotos(const QList<QString> &value)
{
    photos = value;
}
