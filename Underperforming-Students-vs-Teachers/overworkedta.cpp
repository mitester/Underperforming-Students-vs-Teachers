#include "overworkedta.h"

const QString OverworkedTA::DEFAULT_NAME = "Overworked TA";

QPixmap* OverworkedTA::PIC_0 = nullptr;
QPixmap* OverworkedTA::PIC_1 = nullptr;

OverworkedTA::OverworkedTA(QLabel *widget, Row* row, QString name, int maxHp, int speed, int damage) :
    Teacher(widget, row, name, maxHp, speed, damage)
{

}

TimeVariant::Type OverworkedTA::getType() const {return TimeVariant::Type::OVERWORKED_TA;}



