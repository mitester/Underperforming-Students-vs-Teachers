#include "timevariant.h"
#include "game.h"

TimeVariant::TimeVariant(QLabel* widget, Row* row) : QObject(widget), widget(widget), row(row)
{
    widget->setScaledContents(true); //all labels should be scaledContents
}

//when a TimeVariant is deleted
//the widget has to be also deleted
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
