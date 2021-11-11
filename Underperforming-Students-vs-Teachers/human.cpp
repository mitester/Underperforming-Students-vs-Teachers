#include "human.h"
#include <QDebug>

Human::Human()
{
    hp = getMaxHp();
    qDebug() << hp << endl;
}

int Human::getHp() {return hp;}

void Human::setHp(int hp) {this->hp = hp;}
