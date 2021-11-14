#ifndef PANG_H
#define PANG_H

#include "teacher.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class Pang : public Teacher
{
public:
    static const QString defaultName;
    static const int defaultMaxHp{10};
    constexpr static const double defaultSpeed{10.0};
    static const int defaultDamage{10};

    Pang(QWidget *widget,
           QString name = defaultName, int maxHp = defaultMaxHp,
           double speed = defaultSpeed, int damage = defaultDamage);

    void update(); // implementation of the virtual function update()
};

#endif // PANG_H
