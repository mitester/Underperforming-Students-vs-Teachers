#include "gbusstudent.h"
#include "game.h"
#include "redbull.h"

const QString GbusStudent::DEFAULT_NAME = "GBUS Student";

QPixmap* GbusStudent::PIC_0 = nullptr;
QPixmap* GbusStudent::PIC_1 = nullptr;
QPixmap* GbusStudent::PIC_2 = nullptr;

GbusStudent::GbusStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost)
    : SupportStudent(widget, row, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Type GbusStudent::getType() const {return TimeVariant::Type::GBUS_STUDENT;}

//the implementation of the pure virtual update()
void GbusStudent::update()
{
    if(timeConcept == skillSpeed / 2) //pic for preparation
    {
        widget->setPixmap(*PIC_1);
    }
    else if(timeConcept == skillSpeed) //pic for generate redbull
    {
        widget->setPixmap(*PIC_2);

        Game* game = Game::getInstance(); //get the only instance of game

        ClickableLabel* label = new ClickableLabel(game->getParent());

        //set the label correctly with appropriate properties
        label->hide();
        label->move(widget->pos());
        label->setFixedSize(Redbull::SPRITE_WIDTH, Redbull::SPRITE_HEIGHT);
        label->setPixmap(*Redbull::PIC_0);

        //create a redbull
        //register the redbull to mainTimer
        Redbull* s = new Redbull(label);
        game->registerTimeVariant(s);

        timeConcept = 0;
    }
    //give this guy an idle mode
    else if(timeConcept >= skillSpeed / 3 && timeConcept <= skillSpeed / 2)
    {
        widget->setPixmap(*PIC_0);
    }
    //count the time
    timeConcept += Game::BASIC_TIME_UNIT;
}
