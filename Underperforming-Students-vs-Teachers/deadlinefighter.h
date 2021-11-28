#ifndef DEADLINEFIGHTER_H
#define DEADLINEFIGHTER_H

#include "attackstudent.h"

class DeadlineFighter : public AttackStudent
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{200};
    static const int DEFAULT_SKILL_SPEED{2200};
    static const int DEFAULT_TRIGGERED_SKILL_SPEED{600};
    static const int DEFAULT_COST{10};
    static const int DEFAULT_DAMAGE{10};
    static const int DEFAULT_TRIGGER_SKILL_DISTANCE{380};

    static QPixmap* PIC_0;
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;
    static QPixmap* PIC_3;
    static QPixmap* PIC_4;
    static QPixmap* PIC_5;

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

    bool isTriggered() const;

private:
    const int normalSkillSpeed;
    const int triggeredSkillSpeed;
    const int triggerSkillDistance;

    bool triggered = false;

};

#endif // DEADLINEFIGHTER_H
