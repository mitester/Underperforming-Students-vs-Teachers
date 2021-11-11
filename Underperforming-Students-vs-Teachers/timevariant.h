/*
* All classes should be inherited from this
*/

#ifndef TIMEVARIANT_H
#define TIMEVARIANT_H


class TimeVariant
{
public:
    TimeVariant();
    virtual void update() = 0; //restricting all subclasses to react with the global timer signal
};

#endif // TIMEVARIANT_H
