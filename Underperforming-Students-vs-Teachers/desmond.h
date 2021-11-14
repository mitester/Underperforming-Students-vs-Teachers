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
    constexpr static const double DEFAULT_SPEED{10.0};
    static const int DEFAULT_DAMAGE{10};
    constexpr static const double DEFAULT_SKILL_SPEED{10.0};

    double getSkillSpeed() const;
    void setSkillSpeed(double skillSpeed);

    Desmond(QWidget *widget,
           QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
           double speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE, double skillSpeed = DEFAULT_SKILL_SPEED);
    void skill();

    void update(); // implementation of the virtual function update()
private:
    double skillSpeed;
};

#endif // DESMOND_H
