#include <QJsonObject>
#include <QJsonArray>
#include "socialtraffic.h"


SocialTraffic::SocialTraffic(QJsonValue jsonValue)
{
    QJsonObject object = jsonValue.toObject();
    iD = jsonValue.toObject().value("ID").toInt();
    iD = jsonValue.
    siteID = jsonValue.toObject().value("SiteID").toInt();
    site = jsonValue.toObject().value("Site").toString();
    link = jsonValue.toObject().value("Link").toString();
    share = jsonValue.toObject().value("Share").toDouble();
}

QJsonValue SocialTraffic::toJSON()
{
    QJsonObject jsonObject;
    jsonObject.insert("ID", QJsonValue(iD));
    jsonObject.insert("SiteID", QJsonValue(siteID));
    jsonObject.insert("Site", QJsonValue(site));
    jsonObject.insert("Link", QJsonValue(link));
    jsonObject.insert("Share", QJsonValue(share));
    return (QJsonValue(jsonObject));
}

SocialTraffic::SocialTraffic()
{

}

bool SocialTraffic::operator==(const SocialTraffic &obj1) const
{
    if (this->iD == obj1.iD)
        return (true);
    return (false);
}

