#ifndef KELVIN_H
#define KELVIN_H

#include "teacher.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class Kelvin : public Teacher
{

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{10};
    constexpr static const double DEFAULT_SPEED{10.0};
    static const int DEFAULT_DAMAGE{10};

    Kelvin(QWidget *widget,
           QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
           double speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE);

    void update(); // implementation of the virtual function update()
};

#endif // KELVIN_H
