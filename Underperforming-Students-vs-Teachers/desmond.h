#ifndef DESMOND_H
#define DESMOND_H

#include "teacher.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class Desmond : public Teacher
{
public:
    static const QString defaultName;
    static const int defaultMaxHp{10};
    constexpr static const double defaultSpeed{10.0};
    static const int defaultDamage{10};
    constexpr static const double defaultSkillSpeed{10.0};

    double getSkillSpeed() const;
    void setSkillSpeed(double skillSpeed);

    Desmond(QWidget *widget,
           QString name = defaultName, int maxHp = defaultMaxHp,
           double speed = defaultSpeed, int damage = defaultDamage, double skillSpeed = defaultSkillSpeed);

    void update(); // implementation of the virtual function update()
    void skill();
private:
    double skillSpeed;
};

#endif // DESMOND_H
