#ifndef CGAGOD_H
#define CGAGOD_H

#include "attackstudent.h"

class CgaGod : public AttackStudent
{
public:
    static const QString defaultName;
    static const int defaultMaxHp{10};
    static constexpr double defaultSkillSpeed{10.0}; //compiler said it should be constexpr for static double
    static const int defaultCost{10};
    static const int defaultDamage{10};

    CgaGod(QWidget* widget,
                         QString name = defaultName,
                         int maxHp = defaultMaxHp,
                         double skillSpeed = defaultSkillSpeed,
                         int cost = defaultCost,
                         int damage = defaultDamage);

    //the implementation of the pure virtual skill()
    void skill();

    //the implementation of the pure virtual update()
    void update();

};

#endif // CGAGOD_H
