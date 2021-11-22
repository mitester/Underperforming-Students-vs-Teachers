#ifndef KELVIN_H
#define KELVIN_H

#include "teacher.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class Kelvin : public Teacher
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{10};
    static const int DEFAULT_SPEED{5};
    static const int DEFAULT_DAMAGE{10};

    Kelvin(QLabel *widget, Row* row,
           QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
           int speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE);

    TimeVariant::Type getType() const;

    void update(); // implementation of the virtual function update()
};

#endif // KELVIN_H
