#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "item.h"

class VendingMachine : public Item
{
    Q_OBJECT
public:
    static const int DEFAULT_SKILL_SPEED{5000};

    static const int SPRITE_WIDTH{140};
    static const int SPRITE_HEIGHT{182};


    static QPixmap* PIC_0;

    VendingMachine(QLabel* widget, int skillSpeed = DEFAULT_SKILL_SPEED);

    TimeVariant::Type getType() const;

    void update();

private:
    int skillSpeed;
};

#endif // VENDINGMACHINE_H
