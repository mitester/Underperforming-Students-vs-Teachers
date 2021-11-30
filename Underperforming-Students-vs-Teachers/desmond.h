#ifndef DESMOND_H
#define DESMOND_H

#include "teacher.h"

/***
    The class of boss Desmond.

    It is responsible for handling the attack, movement and skill of Desmond.
    It also provides necessary accessors and mutators for manager classes.
    All parameters of `Desmond` such as speed, skillspeed are defined in this class.

*/

class Desmond : public Teacher
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{100};
    static const int DEFAULT_SPEED{1};
    static const int DEFAULT_DAMAGE{10};
    static const int DEFAULT_SKILL_SPEED{600};
    static const int SPEED_INCREASE_COUNTDOWN{500}; // the countdown for desmond's speed increment skill

    static const int SPRITE_WIDTH{121};
    static const int SPRITE_HEIGHT{180};

    static QPixmap* PIC_0;  //preloaded pictures of desmond
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;
    static QPixmap* PIC_3;

    int getSkillSpeed() const;          //accessors
    void setSkillSpeed(int skillSpeed); //mutators

    Desmond(QLabel *widget, Row* row,
           QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
           int speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE, int skillSpeed = DEFAULT_SKILL_SPEED);

    TimeVariant::Type getType() const;

    void update(); // implementation of the virtual function update()
private:
    int skillSpeed;
    int counterSkill = 0; // counter for skill
    int countdown = 0;
    bool speedIncreased = false;
};

#endif // DESMOND_H
