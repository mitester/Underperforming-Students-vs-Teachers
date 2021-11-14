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
    //getter and setter for widget
    QWidget* getWidget();
    void setWidget(QWidget *widget);

    //restricting all subclasses to react with the global timer signal
    virtual void update() = 0;

protected:
    TimeVariant(QWidget *widget);

    QWidget *widget; //every TimeVariant owns a QWidget

};

#endif // TIMEVARIANT_H
