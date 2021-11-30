#include "teacher.h"
#include "human.h"
#include <algorithm>
#include <queue>
#include "row.h"
#include "timevariant.h"
#include "human.h"
#include "assignment.h"
#include "item.h"
#include "kelvin.h"
#include <QDebug>

Teacher::Teacher(QLabel *widget, Row* row, QString name, int maxHp, int speed, int damage) :
    Human(widget, row, name, maxHp), speed(speed), damage(damage)
{
    player->setMedia(QUrl("qrc:/sounds/hit.wav"));
}

TimeVariant::Category Teacher::getCategory() const {return TimeVariant::Category::TEACHER;}

int Teacher::getDamage() const {
    return damage;
}

void Teacher::setDamage(int damage) {
    this->damage = damage;
}

int Teacher::getSpeed() const {
    return speed;
}

void Teacher::setSpeed(int speed) {
    this->speed = speed;
}

void Teacher::update() {    // a null implementation.

}

