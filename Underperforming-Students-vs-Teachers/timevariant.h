/*
* All classes should be inherited from this
*/

#ifndef TIMEVARIANT_H
#define TIMEVARIANT_H

#include <QWidget>
#include <QObject>

class TimeVariant : public QObject
{
    Q_OBJECT
public:

    enum class Type{
        SLEEP_DEPRIVED_STUDENT,
        DEADLINE_FIGHTER,
        CGA_GOD,
        SHAMELESS_STUDENT,
        TEACHERS_PET,
        GBUS_STUDENT,
        OVERWORKED_TA,
        KELVIN,
        PANG,
        DESMOND,
        REDBULL,
        ASSIGNMENT,
        VENDING_MACHINE
    };

    //getter and setter for widget
    QWidget* getWidget();
    void setWidget(QWidget *widget);
    double getDistanceFromLeft() const;

    //restricting all subclasses to react with the global timer signal
    virtual void update() = 0;

protected:
    TimeVariant(QWidget *widget);

    QWidget *widget; //every TimeVariant owns a QWidget

};

#endif // TIMEVARIANT_H
