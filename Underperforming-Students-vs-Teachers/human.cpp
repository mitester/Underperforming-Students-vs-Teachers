#include "human.h"

Human::Human(QLabel *widget, Row* row, QString name, int maxHp) : TimeVariant(widget, row), name(name), hp(maxHp), maxHp(maxHp)
{
    widget->setFixedSize(SPRITE_WDITH, SPRITE_HEIGHT);
}

//getter and setter for name
QString Human::getName() const {return name;}
void Human::setName(QString name) {this->name = name;}

//getter and setter for maxHp
int Human::getMaxHp() const {return maxHp;}
void Human::setMaxHp(int maxHp) {this->maxHp = maxHp;}

//getter and setter for hp
int Human::getHp() const {return hp;}
void Human::setHp(int hp) {this->hp = hp;}

