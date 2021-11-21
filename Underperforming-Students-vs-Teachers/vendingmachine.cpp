#include "vendingmachine.h"

VendingMachine::VendingMachine(QLabel* widget, Row* row) : Item(widget, row)
{

}

TimeVariant::Type VendingMachine::getType() const
{
    return TimeVariant::Type::VENDING_MACHINE;
}

void VendingMachine::update()
{

}
