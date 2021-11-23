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
    if(timeConcept == skillSpeed)
    {
        Game* game = Game::getInstance();

        ClickableLabel* label = new ClickableLabel(game->getParent());

        label->hide();
        label->move(widget->pos());
        label->setFixedSize(Redbull::SPRITE_WIDTH, Redbull::SPRITE_HEIGHT);
        label->setPixmap(*Redbull::PIC_0);

        Redbull* s = new Redbull(label);
        game->registerTimeVariant(s);

        timeConcept = 0;
    }
    timeConcept += Game::BASIC_TIME_UNIT;
}
