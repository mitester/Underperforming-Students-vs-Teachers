#include "timevariant.h"
#include "game.h"

TimeVariant::TimeVariant(QLabel* widget, Row* row) : QObject(widget), widget(widget), row(row)
{
    widget->setScaledContents(true);
}

TimeVariant::~TimeVariant()
{
    widget->hide();
    widget->setEnabled(false);
    widget->deleteLater();
}

QLabel* TimeVariant::getWidget() const {return widget;}

void TimeVariant::setWidget(QLabel* widget) {this->widget = widget;}

int TimeVariant::getDistanceFromLeft() const {
    return this->widget->x();
}

Row* TimeVariant::getRow() const {
    return row;
}
