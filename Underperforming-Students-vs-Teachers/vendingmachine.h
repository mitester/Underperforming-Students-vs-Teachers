#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "item.h"

class VendingMachine : public Item
{
    Q_OBJECT
public:
    static const int DEFAULT_SKILL_SPEED{1000};

    static QPixmap* PIC_0;

    VendingMachine(QLabel* widget, int skillSpeed = DEFAULT_SKILL_SPEED);

    TimeVariant::Type getType() const;

    void update();

private:
    int skillSpeed;
};

#endif // VENDINGMACHINE_H
