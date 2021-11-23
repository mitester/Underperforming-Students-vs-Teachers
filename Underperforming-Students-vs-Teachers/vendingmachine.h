#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "item.h"

class VendingMachine : public Item
{
    Q_OBJECT
public:
    static const int DEFAULT_SKILL_SPEED{1500};

    static const int SPRITE_WIDTH{200};
    static const int SPRITE_HEIGHT{260};


    static QPixmap* PIC_0;

    VendingMachine(QLabel* widget, int skillSpeed = DEFAULT_SKILL_SPEED);

    TimeVariant::Type getType() const;

    void update();

private:
    int skillSpeed;
};

#endif // VENDINGMACHINE_H
