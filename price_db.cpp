#include "price_db.h"

price_db::price_db(QString &FromWhere, QString &Standart, QString &WidthProfile, QString &HightProfile, QString &WallThickness,
                   QString &Steel, QString &Tonnag, QString &WholesalePrice, QString &SellingPrice)
{
    this->FromWhere = FromWhere;
    this->Standart = Standart;
    this->WidthProfile = WidthProfile;
    this->HightProfile = HightProfile;
    this->WallThickness = WallThickness;
    this->Steel = Steel;
    this->Tonnag = Tonnag;
    this->WholesalePrice = WholesalePrice;
    this->SellingPrice = SellingPrice;
}
