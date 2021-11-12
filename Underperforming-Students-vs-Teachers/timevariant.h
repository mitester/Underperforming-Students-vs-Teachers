/*
* All classes should be inherited from this
*/

#ifndef TIMEVARIANT_H
#define TIMEVARIANT_H

#include <QWidget>

class TimeVariant
{
protected:
    TimeVariant(QWidget *widget);

    QWidget *widget; //every TimeVariant owns a QWidget

    //getter and setter for widget
    QWidget* getWidget();
    void setWidget(QWidget *widget);

    //restricting all subclasses to react with the global timer signal
    virtual void update() = 0;


};

#endif // TIMEVARIANT_H
