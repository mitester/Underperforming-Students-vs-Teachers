#ifndef DESMOND_H
#define DESMOND_H

#include "teacher.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class Desmond : public Teacher
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{10};
    static const int DEFAULT_SPEED{1000};
    static const int DEFAULT_DAMAGE{10};
    static const int DEFAULT_SKILL_SPEED{1000};

    int getSkillSpeed() const;
    void setSkillSpeed(int skillSpeed);

    Desmond(QLabel *widget, Row* row,
           QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
           int speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE, int skillSpeed = DEFAULT_SKILL_SPEED);

    TimeVariant::Type getType() const;

    void skill();

    void update(); // implementation of the virtual function update()
private:
    int skillSpeed;
};

#endif // DESMOND_H
