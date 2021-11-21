#ifndef REDBULL_H
#define REDBULL_H

#include "item.h"
#include "clickablelabel.h"

class Redbull : public Item
{
    Q_OBJECT
public:
    static const int DEFAULT_ENERGY = 10;
    Redbull(ClickableLabel* widget, int energy = DEFAULT_ENERGY, Row* row = nullptr);

    //getter & settter for energy
    int getEnergy() const;
    void setEnergy(int energy);

    //override
    TimeVariant::Type getType() const;

    //override
    void update();

private:
    int energy;

    void pressed(); //private function handling redbull is pressed
};

#endif // REDBULL_H
