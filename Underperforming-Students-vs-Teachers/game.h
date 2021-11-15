/***
* It guards the whole game
* It is the central game manager
* This class is a singleton class since only one game object is allowed for each game
*/
#ifndef GAME_H
#define GAME_H

#include "timevariant.h"
#include "teacher.h"
#include "row.h"

#include <QTimer>
#include <QProgressBar>
#include <climits>

class Game : public QObject
{
    Q_OBJECT

public:
    static const int BASIC_TIME_UNIT{1}; //it is the basic time unit of QTimer
    static const int DEFAULT_REDBULL_NUMBER{10}; // it is the default redbull number
    static const int NUMBER_OF_ROW{4}; //it is the number of row of the map
    static const int NUMBER_OF_COLUMN{10};
    static const int MAX{INT_MAX}; //the maximum integer

    enum class GameStatus {STUDENT_WON, TEACHER_WON, BATTLING, PAUSED};

    //get instance with its parent
    static Game* getInstance(QObject* parent = nullptr);

    //getter and setter of redbullNum
    int getRedbullNum() const;
    bool addRedbull(int n = 1); //default value of n is 1. Decrease it by passing a negative value
                                //return true if added sucessfully, otherwise, false

    //the timeVariant will be linked with the timer
    //and will call his update() function when timeout()
    void registerTimeVariant(TimeVariant *timeVariant);

    //getter & setter of gameStatus
    GameStatus getGameStatus() const;
    void setGameStatus(GameStatus status);

    //it checks if the game ended
    void checkTerminated();

    //game controller
    //return a bool value indicating if the operation succeeded
    bool start();
    bool pause();
    //bool stop(); no need for this. Just close the window bounded with this game

private:
    explicit Game(QObject* parent = nullptr);
    ~Game();

    static Game* instance;

    QTimer *timer; //It emits timeout() every BASIC_TIME_UNIT millisecond

    int redbullNum = DEFAULT_REDBULL_NUMBER; //stores how many Redbulls user have

    //an array of Row* storing the row information for the i-th row
    Row* rows[NUMBER_OF_ROW]; //statically allocated thus no memory concern

    //a variable stores if the game starts, it can be changed by calling Game::start(), Game::pause(), Game::stop()
    bool isStart = false;

    //it generates teacher randomly
    Teacher* generateTeacher();

    GameStatus gameStatus = GameStatus::PAUSED;
};

#endif // GAME_H
