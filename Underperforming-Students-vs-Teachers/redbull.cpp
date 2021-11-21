#include "redbull.h"

Redbull::Redbull(ClickableLabel* widget, int energy, Row* row) : Item(widget, row), energy(energy)
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

}

void Redbull::pressed()
{

}
