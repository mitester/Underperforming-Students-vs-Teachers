#ifndef OVERWORKEDTA_H
#define OVERWORKEDTA_H

#include "teacher.h"
#include "human.h"
#include <algorithm>
#include <queue>
#include "row.h"
#include "timevariant.h"
#include "human.h"
#include "assignment.h"
#include "item.h"
#include "kelvin.h"
#include <QLabel>

/***
    Date: 11/13/2021
    The class of Teacher OverworkedTa.
    It is a subclass of Teacher, which represents the OverworkedTa.
    All its parameters & pictures are stored as static memeber of the class.
*/

class OverworkedTA : public Teacher
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{50};
    static const int DEFAULT_SPEED{2};
    static const int DEFAULT_DAMAGE{1};

    static QPixmap* PIC_0;  //preloaded pictures of the pixmap
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;
    static QPixmap* PIC_3;

    explicit OverworkedTA(QLabel *widget, Row* row,
                          QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
                          int speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE);

    TimeVariant::Type getType() const;  //virtual function implemented
    void update();  //virtual function implemented
};

#endif // OVERWORKEDTA_H
