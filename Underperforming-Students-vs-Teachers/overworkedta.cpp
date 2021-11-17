#include "overworkedta.h"

const QString OverworkedTA::DEFAULT_NAME = "Overworked TA";

OverworkedTA::OverworkedTA(QLabel *widget, Row* row, QString name, int maxHp, double speed, int damage) :
    Teacher(widget, row, name, maxHp, speed, damage)
{

}

TimeVariant::Type OverworkedTA::getType() const {return TimeVariant::Type::OVERWORKED_TA;}

void OverworkedTA::update() {

}


