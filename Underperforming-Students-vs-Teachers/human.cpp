#include "human.h"
#include <QDebug>

Human::Human()
{
    hp = getMaxHp();
}

int Human::getHp() {return hp;}

void Human::setHp(int hp) {this->hp = hp;}
