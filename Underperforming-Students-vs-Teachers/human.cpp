#include "human.h"

Human::Human(QWidget *widget, QString name, int maxHp) : TimeVariant(widget), name(name), hp(maxHp), maxHp(maxHp)
{

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

