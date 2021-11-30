#include "vendingmachine.h"
#include "game.h"
#include "redbull.h"
#include <QDebug>

QPixmap* VendingMachine::PIC_0 = nullptr;

VendingMachine::VendingMachine(QLabel* widget, int skillSpeed) : Item(widget, nullptr), skillSpeed(skillSpeed)
{

}

TimeVariant::Type VendingMachine::getType() const
{
    return TimeVariant::Type::VENDING_MACHINE;
}

void VendingMachine::update()
{
    //if it is time for it to emit Redbull
    if(timeConcept == skillSpeed)
    {
        Game* game = Game::getInstance();

        //create a label
        ClickableLabel* label = new ClickableLabel(game->getParent());

        //set the label with appropriate properties
        label->hide();
        label->move(widget->pos());
        label->setFixedSize(Redbull::SPRITE_WIDTH, Redbull::SPRITE_HEIGHT);
        label->setPixmap(*Redbull::PIC_0);

        //create a redbull object
        Redbull* s = new Redbull(label);
        //register it to the mainTimer
        game->registerTimeVariant(s);

        //reset the time counter
        timeConcept = 0;
    }
    timeConcept += Game::BASIC_TIME_UNIT; //count the time
}
