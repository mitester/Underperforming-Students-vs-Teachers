/***
 * This is the class of Deadline Fighter
 * inherits from AttackStudent
 */
#ifndef DEADLINEFIGHTER_H
#define DEADLINEFIGHTER_H

#include "attackstudent.h"

class DeadlineFighter : public AttackStudent
{
    Q_OBJECT

public:
    //some constants defined a Deadline Fighter
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{200};
    static const int DEFAULT_SKILL_SPEED{2200};
    static const int DEFAULT_TRIGGERED_SKILL_SPEED{600};
    static const int DEFAULT_COST{20};
    static const int DEFAULT_DAMAGE{10};
    static const int DEFAULT_TRIGGER_SKILL_DISTANCE{380};

    //sprite pictures
    static QPixmap* PIC_0;
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;
    static QPixmap* PIC_3;
    static QPixmap* PIC_4;
    static QPixmap* PIC_5;

    //constructor
    DeadlineFighter(QLabel* widget, Row* row,
                         QString name = DEFAULT_NAME,
                         int maxHp = DEFAULT_MAX_HP,
                         int normalSkillSpeed = DEFAULT_SKILL_SPEED,
                         int triggeredSkillSpeed = DEFAULT_TRIGGERED_SKILL_SPEED,
                         int cost = DEFAULT_COST,
                         int damage = DEFAULT_DAMAGE,
                         int triggerSkillDistance = DEFAULT_TRIGGER_SKILL_DISTANCE);

    TimeVariant::Type getType() const;

    //the implementation of the pure virtual update()
    void update();

    //get the value of private member variable, triggered
    bool isTriggered() const;

private:
    //since Deadline Fighter has two different modes, normal and rage
    //so these variable records different quantities when they're in different modes
    const int normalSkillSpeed;
    const int triggeredSkillSpeed;
    const int triggerSkillDistance;

    //triggered is false => normal mode
    //triggered is true => rage mode
    bool triggered = false;

};

#endif // DEADLINEFIGHTER_H
