#ifndef CGAGOD_H
#define CGAGOD_H

#include "attackstudent.h"

class CgaGod : public AttackStudent
{
public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{10};
    static constexpr double DEFAULT_SKILL_SPEED{10.0}; //compiler said it should be constexpr for static double
    static const int DEFAULT_COST{10};
    static const int DEFAULT_DAMAGE{10};

    CgaGod(QWidget* widget,
                         QString name = DEFAULT_NAME,
                         int maxHp = DEFAULT_MAX_HP,
                         double skillSpeed = DEFAULT_SKILL_SPEED,
                         int cost = DEFAULT_COST,
                         int damage = DEFAULT_DAMAGE);

    //the implementation of the pure virtual skill()
    void skill();

    //the implementation of the pure virtual update()
    void update();

};

#endif // CGAGOD_H
