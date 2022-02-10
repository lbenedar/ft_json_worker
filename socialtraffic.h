#ifndef SOCIALTRAFFIC_H
#define SOCIALTRAFFIC_H

#include <QString>
#include <QJsonObject>

class SocialTraffic
{
public:
    int iD;
    int siteID;
    QString site;
    QString link;
    double share;

    SocialTraffic(QJsonValue jsonValue);
    SocialTraffic();

    QJsonValue toJSON();
    bool operator ==(const SocialTraffic &obj1) const;
};

#endif // SOCIALTRAFFIC_H
