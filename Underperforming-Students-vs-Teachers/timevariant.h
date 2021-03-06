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
    //an enum class which stores all TimeVariant Types
    enum class Type
    {
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
        VENDING_MACHINE,
        EMPTY
    };

    //an enum class which stores all TimeVariant Categories
    enum class Category
    {
        ATTACK_STUDENT,
        SUPPORT_STUDENT,
        TEACHER,
        ITEM
    };

    //getter and setter for widget
    QLabel* getWidget() const;
    void setWidget(QLabel *widget);

    //restricting all subclasses to react with the global timer signal
    //it is called per BASIC_TIME_UNIT defined in Game.h
    virtual void update() = 0;

    //restricting all subclasses to provide an interface to return back their type & category
    virtual TimeVariant::Type getType() const = 0;
    virtual TimeVariant::Category getCategory() const = 0;

    //get their widget x coordinate
    int getDistanceFromLeft() const;

    //get the row object belongs to this TimeVariant object
    Row* getRow() const;


protected:
    //constructor
    TimeVariant(QLabel *widget, Row* row);
    ~TimeVariant();

    QLabel* widget; //every TimeVariant owns a QWidget
    Row* row; //stores which row that TimeVariant belongs

    int timeConcept = 0; //every TimeVariant has time concept
                            //it adds one basic unit time after receive one timeout()
                            //it belongs to [0,speed)
};

#endif // TIMEVARIANT_H
