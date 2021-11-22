#include "vendingmachine.h"

VendingMachine::VendingMachine(QLabel* widget) : Item(widget, nullptr)
{

}

TimeVariant::Type VendingMachine::getType() const
{
    return TimeVariant::Type::VENDING_MACHINE;
}

void VendingMachine::update()
{

}
