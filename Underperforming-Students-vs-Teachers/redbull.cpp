#include "redbull.h"

Redbull::Redbull(ClickableLabel* widget, int energy, int vx, int vy, int ay) : Item(widget, nullptr),
    energy(energy), vx_initial(vx), vx(vx), vy_initial(vy), vy(vy), ay(ay)
{
    connect(widget, &ClickableLabel::clicked, this, &Redbull::pressed);
}

int Redbull::getEnergy() const
{
    return energy;
}

void Redbull::setEnergy(int energy)
{
    this->energy = energy;
}

TimeVariant::Type Redbull::getType() const
{
    return TimeVariant::Type::REDBULL;
}

void Redbull::update()
{
    if(isPressed)
    {
        //fly to the redbull storage place
    }
    else
    {
        if(vy == -vy_initial) return; //parabola completed
        widget->move(widget->x() + vx, widget->y() + vy);
        vy += ay;
    }

}

void Redbull::pressed()
{
    isPressed = true;
}
