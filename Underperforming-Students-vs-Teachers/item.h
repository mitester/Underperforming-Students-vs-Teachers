#ifndef ITEM_H
#define ITEM_H

#include "timevariant.h"

class Item : public TimeVariant
{
    Q_OBJECT

public:
    TimeVariant::Category getCategory() const;

protected:
    Item(QLabel* widget, Row* row = nullptr);
};

#endif // ITEM_H
