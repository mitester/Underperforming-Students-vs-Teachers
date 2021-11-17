/***
* All classes should be inherited from this
*/

#ifndef TIMEVARIANT_H
#define TIMEVARIANT_H

#include <QLabel>
#include <QObject>

class Row;

class TimeVariant : public QObject
{
    Q_OBJECT
public:
    enum class Type
    {
        SLEEP_DEPRIVED_STUDENT,
        DEADLINE_STUDENT,
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

    enum class Category
    {
        ATTACK_STUDENT,
        SUPPORT_STUDENT,
        TEACHER,
        ITEM
    };

    //getter and setter for widget
    QLabel* getWidget();
    void setWidget(QLabel *widget);

    //restricting all subclasses to react with the global timer signal
    virtual void update() = 0;

    //restricting all subclasses to provide an interface to return back their type & category
    virtual TimeVariant::Type getType() const = 0;
    virtual TimeVariant::Category getCategory() const = 0;
    double getDistanceFromLeft() const;
    Row* getRow();


protected:
    TimeVariant(QLabel *widget, Row* row);

    QLabel* widget; //every TimeVariant owns a QWidget
    Row* row; //stores which row that TimeVariant belongs

};

#endif // TIMEVARIANT_H
