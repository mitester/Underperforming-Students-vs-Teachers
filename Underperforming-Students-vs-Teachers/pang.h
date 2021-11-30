#ifndef PANG_H
#define PANG_H

#include "teacher.h"

/***
    Date: 11/13/2021
    The class of Teacher Pang.
    It is a subclass of Teacher, which represents the Pang.
    All its parameters & pictures are stored as static memeber of the class.
*/

class Pang : public Teacher
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{200};
    static const int DEFAULT_SPEED{4};
    static const int DEFAULT_DAMAGE{1};

    static QPixmap* PIC_0;  //preloaded pictures
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;
    static QPixmap* PIC_3;

    Pang(QLabel *widget, Row* row,
           QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
           int speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE);

    TimeVariant::Type getType() const;  //pure virtual functions implemented
    void update();  //pure virtual function implemented

};

#endif // PANG_H
