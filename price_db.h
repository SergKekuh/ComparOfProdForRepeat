
#ifndef PRICE_DB_H
#define PRICE_DB_H

#include <QObject>

class price_db
{
public:
    price_db(QString &FromWhere, QString &Standart, QString &WidthProfile, QString &HightProfile, QString &WallThickness,
             QString &Steel, QString &Tonnag, QString &WholesalePrice, QString &SellingPrice);
    QString FromWhere;
    QString Standart;
    QString WidthProfile;
    QString HightProfile;
    QString WallThickness;
    QString Steel;
    QString Tonnag;
    QString WholesalePrice;
    QString SellingPrice;
};

#endif // PRICE_DB_H
