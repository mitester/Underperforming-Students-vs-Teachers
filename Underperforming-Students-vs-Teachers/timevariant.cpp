#include "timevariant.h"

TimeVariant::TimeVariant(QLabel* widget, Row* row) : QObject(widget), widget(widget), row(row)
{
    widget->setScaledContents(true);
    widget->setFixedSize(spriteWidth, spriteHeight);
}

QLabel* TimeVariant::getWidget() {return widget;}

void TimeVariant::setWidget(QLabel* widget) {this->widget = widget;}

double TimeVariant::getDistanceFromLeft() const {
    return this->widget->x();
}

Row* TimeVariant::getRow() const {
    return row;
}
