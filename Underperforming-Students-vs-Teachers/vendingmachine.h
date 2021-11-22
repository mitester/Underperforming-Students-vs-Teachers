#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "item.h"

class VendingMachine : public Item
{
    Q_OBJECT
public:
    VendingMachine(QLabel* widget);

    TimeVariant::Type getType() const;

    void update();
};

#endif // VENDINGMACHINE_H