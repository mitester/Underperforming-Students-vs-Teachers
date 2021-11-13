#ifndef DESMOND_H
#define DESMOND_H

#include "teacher.h"

class Desmond : public Teacher
{
public:
    static const QString defaultName;
    static const int defaultMaxHp{10};
    constexpr static const double defaultSpeed{10.0};
    static const int defaultAtk{10};

    Desmond(QWidget *widget,
           QString name = defaultName, int maxHp = defaultMaxHp,
           double speed = defaultSpeed, int atk = defaultAtk);
};

#endif // DESMOND_H
