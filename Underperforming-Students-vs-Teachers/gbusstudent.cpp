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
    if(timeConcept == skillSpeed / 2)
    {
        widget->setPixmap(*PIC_1);
    }
    else if(timeConcept == skillSpeed)
    {
        widget->setPixmap(*PIC_2);

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
    else if(timeConcept >= skillSpeed / 3 && timeConcept <= skillSpeed / 2)
    {
        widget->setPixmap(*PIC_0);
    }
    timeConcept += Game::BASIC_TIME_UNIT;
}
