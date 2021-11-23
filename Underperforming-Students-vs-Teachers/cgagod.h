#ifndef CGAGOD_H
#define CGAGOD_H

#include "attackstudent.h"

class CgaGod : public AttackStudent
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{10};
    static const int DEFAULT_SKILL_SPEED{1000};
    static const int DEFAULT_COST{10};
    static const int DEFAULT_DAMAGE{10};

    static QPixmap* PIC_0;
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;

    CgaGod(QLabel* widget, Row* row,
                         QString name = DEFAULT_NAME,
                         int maxHp = DEFAULT_MAX_HP,
                         int skillSpeed = DEFAULT_SKILL_SPEED,
                         int cost = DEFAULT_COST,
                         int damage = DEFAULT_DAMAGE);

    TimeVariant::Type getType() const;

    //the implementation of the pure virtual update()
    void update();

};

#endif // CGAGOD_H
