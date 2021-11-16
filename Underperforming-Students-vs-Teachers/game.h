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
#include <QSet>

class Game : public QObject
{
    Q_OBJECT

public:
    static const int BASIC_TIME_UNIT{20}; //it is the basic time unit of QTimer
                                          //emit timeout() signal in 50Hz
    static const int DEFAULT_REDBULL_NUMBER{10}; // it is the default redbull number
    static const int NUMBER_OF_ROW{4}; //it is the number of row of the map
    static const int NUMBER_OF_COLUMN{10};
    static const int MAX{INT_MAX}; //the maximum integer

    enum class GameStatus {STUDENT_WON, TEACHER_WON, BATTLING, PAUSED};

    //get instance with its parent
    static Game* getInstance(QWidget* parent = nullptr);

    //getter and setter of redbullNum
    int getRedbullNum() const;
    bool addRedbull(int n = 1); //default value of n is 1. Decrease it by passing a negative value
                                //return true if added sucessfully, otherwise, false

    //the timeVariant will be linked with the timer
    //and will call his update() function when timeout()
    void registerTimeVariant(TimeVariant *timeVariant);

    //getter of row[i]
    Row* getRowAt(int i) const;

    //getter & setter of gameStatus
    GameStatus getGameStatus() const;
    void setGameStatus(GameStatus status);

    //game controller
    //return a bool value indicating if the operation succeeded
    bool start();
    bool pause();
    //bool stop(); no need for this. Just close the window bounded with this game

private:
    explicit Game(QWidget* parent = nullptr);
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

    //They store the number that leads to create themselves
    //They change as progress value changes
    QSet<int> generateOverworkedTAEvents;
    QSet<int> generateKelvinEvents;
    QSet<int> generatePangEvents;
    QSet<int> generateDesmondEvents;

    //for recording the bounds of the sorted set
    //it is an close interval -> [a,b]
    struct Interval
    {
        Interval(int a, int b) {setInterval(a,b);}
        int min;
        int max;

        //return if x is in between the interval, both inclusive
        bool contains(int x) {return x >= min && x <= max;}
        void setMin(int a) {min = a;}
        void setMax(int b) {max = b;}
        void setInterval(int a, int b) {min = a; max = b;}
    };

    //intervals indicating the boundaries in their sets
    //changes as progress changes
    //total of 20 events
    int totalNumberofEvents = 20;
    Interval overworkedTAEventsInterval{0,14};
    Interval KelvinEventsInterval{15,16};
    Interval PangEventsInterval{17,18};
    Interval DesmondEventsInterval{19,19};

    //Interval indicating number of teachers should be generated
    //changes as progress changes
    Interval numberOfTeachers{1,3};

    GameStatus gameStatus = GameStatus::PAUSED;

    QProgressBar* progressBar;

    //this is not the same as the one in TimeVariant
    //tho it guards the game progress by listening to the global timer signal
    void update();

    //it checks if the game ended. Return true if terminated. Otherwise, false.
    //By calling getGameStatus() to get the terminated reason
    bool checkTerminated();

    //re-calculate the prob. of generating each teacher
    //call it after their events number is changed
    void reCalculateGenerateTeacherProb();

    QWidget* parent;
};

#endif // GAME_H
