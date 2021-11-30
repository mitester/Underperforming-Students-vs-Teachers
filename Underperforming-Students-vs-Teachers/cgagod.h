/***
* The class of the Attack Student, CgaGod
* inherits from the class AttackStudent
*/
#ifndef CGAGOD_H
#define CGAGOD_H

#include "attackstudent.h"

class CgaGod : public AttackStudent
{
    Q_OBJECT

public:
    //some constants defined the CgaGod properties
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{1500};
    static const int DEFAULT_SKILL_SPEED{2400}; //this must be a multiple of 2 * BASIC_GAME_UNIT
    static const int DEFAULT_COST{30};
    static const int DEFAULT_DAMAGE{40};

    //sprite pictures for assignment
    //preloaded in GameWindow
    static QPixmap* PIC_0;
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;

    //constructor
    CgaGod(QLabel* widget, Row* row,
                         QString name = DEFAULT_NAME,
                         int maxHp = DEFAULT_MAX_HP,
                         int skillSpeed = DEFAULT_SKILL_SPEED,
                         int cost = DEFAULT_COST,
                         int damage = DEFAULT_DAMAGE);

    //inherits from TimeVariant getType
    TimeVariant::Type getType() const;

    //the implementation of the pure virtual update()
    void update();

};

#endif // CGAGOD_H
