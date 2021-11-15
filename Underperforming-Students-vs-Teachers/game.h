/*
* It guards the whole game
* It is the central game manager
*/
#ifndef GAME_H
#define GAME_H

#include "timevariant.h"
#include "teacher.h"

#include <QTimer>
#include <QProgressBar>

class Game : public QObject
{
    Q_OBJECT

public:
    static const int BASIC_TIME_UNIT{1}; //it is the basic time unit of QTimer
    static const int DEFAULT_REDBULL_NUMBER{10}; // it is the default redbull number
    static const int NUMBER_OF_ROW{4}; //it is the number of row of the map

    explicit Game(QObject* parent = nullptr);

    //getter and setter of redbullNum
    int getRedbullNum() const;
    bool addRedbull(int n = 1); //default value of n is 1. Decrease it by passing a negative value
                                //return true if added sucessfully, otherwise, false

    //the timeVariant will be linked with the timer
    //and will call his update() function when timeout()
    void registerTimeVariant(TimeVariant *timeVariant);

    //it checks if the game terminated
    bool isTerminated();

private:
    QTimer *timer; //It emits timeout() every BASIC_TIME_UNIT millisecond

    int redbullNum = DEFAULT_REDBULL_NUMBER; //stores how many Redbulls user have

    //TODO: add an array of Row


};

#endif // GAME_H
