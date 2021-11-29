/***
* base class of all items
* inherits from TimeVariant
*/
#ifndef ITEM_H
#define ITEM_H

#include "timevariant.h"
#include <QPixmap>

class Item : public TimeVariant
{
    Q_OBJECT

public:
    TimeVariant::Category getCategory() const;
    static QPixmap* EXPLOSION_0;
    static QPixmap* EXPLOSION_1;
    static QPixmap* EXPLOSION_2;

protected:
    Item(QLabel* widget, Row* row = nullptr);
};

#endif // ITEM_H
