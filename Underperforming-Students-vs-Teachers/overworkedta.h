#ifndef OVERWORKEDTA_H
#define OVERWORKEDTA_H

#include "teacher.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class OverworkedTA : public Teacher
{
public:
    static const QString defaultName;
    static const int defaultMaxHp{10};
    constexpr static const double defaultSpeed{10.0};
    static const int defaultAtk{10};

    explicit OverworkedTA(QWidget *widget,
                          QString name = defaultName, int maxHp = defaultMaxHp,
                          double speed = defaultSpeed, int atk = defaultAtk);

    void update(); // implementation of the virtual function update()
protected:
private:
};

#endif // OVERWORKEDTA_H
