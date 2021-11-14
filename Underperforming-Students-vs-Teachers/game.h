/*
* It guards the whole game
* It is the central game manager
*/
#ifndef GAME_H
#define GAME_H

#include "timevariant.h"

#include <QTimer>

class Game : public QObject
{
    Q_OBJECT

public:
    static const int BASIC_TIME_UNIT{1}; //it is the basic time unit of QTimer
    static const int DEFAULT_REDBULL_NUMBER{10}; // it is the default redbull number

    Game();
    ~Game();

    //getter and setter of redbullNum
    int getRedbullNum() const;
    void addRedbull(int n = 1); //default value is 1. Decrease it by passing a negative value

    //the timeVariant will be linked with the timer
    //and will call his update() function when timeout()
    void registerTimeVariant(TimeVariant *timeVariant);

private:
    QTimer *timer; //It emits timeout() every BASIC_TIME_UNIT millisecond

    int redbullNum = DEFAULT_REDBULL_NUMBER; //stores how many Redbulls user have
};

#endif // GAME_H
