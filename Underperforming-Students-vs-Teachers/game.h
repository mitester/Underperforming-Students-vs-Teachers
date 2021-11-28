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
#include <QSize>
#include <QTime>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class SpriteCard;
class Desmond;

class Game : public QObject
{
    Q_OBJECT

public:
    static const QString GAME_NAME;
    static const int BASIC_TIME_UNIT{20};           //it is the basic time unit of QTimer
                                                    //emit timeout() signal in 50Hz
    static const int DEFAULT_REDBULL_NUMBER{100};    // it is the default redbull number
    static const int NUMBER_OF_ROW{5};              //it is the number of row of the map
    static const int NUMBER_OF_COLUMN{9};
    static const int MAX{INT_MAX}; //the maximum integer

    const static int GRID_UP {30};
    const static int GRID_DOWN {625};
    const static int GRID_INTERVAL_VERTICAL {115};     // the interval between two tiles
    const static int GRID_INTERVAL_HORIZONTAL {97};
    const static int GRID_LEFT {280};        // the position of the leftmost tile
    const static int GRID_RIGHT {1200};         // the position of the rightmost tile
    const static int TEA_GEN_POS {1200};     // the generation position of teachers
    const static int TEA_END_POS {95};       // the end position of teachers (reached this point implies teacher victory)

    const static int GAME_ENDED_LABEL_X{300};
    const static int GAME_ENDED_LABEL_Y{100};
    const static int GAME_ENDED_LABEL_WIDTH{896};
    const static int GAME_ENDED_LABEL_HEIGHT{504};
    static QPixmap* GAME_SCENE_FAIL;
    static QPixmap* GAME_SCENE_PASS;


    const static int GAME_DURATION{180000}; //game duration in msecs
    static Desmond* desmond;

    static QPoint REDBULL_POS;
//    const static int SPRITE_HEIGHT {128};
//    const static int SPRITE_WIDTH {100};
//    const static int ASS_HEIGHT {37};
//    const static int ASS_WIDTH {45};

    static QSize currentSize;
    static void move(QWidget* w, double xPercent, double yPercent);   //move a QWidget to the correspond absolute position given relative position
    //How to use: pass in (w, 10, 15.7) means move w, 10% and 15.7%

    enum class GameStatus {STUDENT_WON, TEACHER_WON, BATTLING, PAUSED};

    //get instance with its parent
    static Game* getInstance(QWidget* parent = nullptr);

    TimeVariant::Type selectedSprite = TimeVariant::Type::EMPTY;
    SpriteCard* selectedCard = nullptr;

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

    QWidget* getParent() const;

    QTimer* getMainTimer() const;

    //return current time left in hh:mm form
    QString getCurrentTimeLeft() const;

    static int getCost(TimeVariant::Type student); //return the cost of the given type

private:
    explicit Game(QWidget* parent = nullptr);
    Game(Game& game) = delete;
    void operator=(const Game&) = delete;
    ~Game();

    static Game* instance;

    QTimer *mainTimer; //It emits timeout() every BASIC_TIME_UNIT millisecond

    int redbullNum = DEFAULT_REDBULL_NUMBER; //stores how many Redbulls user have

    //an array of Row* storing the row information for the i-th row
    Row* rows[NUMBER_OF_ROW]; //statically allocated thus no memory concern

    //it generates teacher randomly
    void generateTeacher();
    QTimer* generatingTimer; //it handles the teacher generating frequency
    int generatingTimerUpperBound = 10001; //exclusive upper bound
    int generatingTimerLowerBound = 5000; //inclusive upper bound
    int getRandomInterval() const; //get a random interval between [generatingLowerBound, generatingUpperBound)

    //it holds and teacher kind boundaries
    int generatingTeacherUpperBound = 5;
    int generatingTeacherLowerBound = 0;

    GameStatus gameStatus = GameStatus::PAUSED;

    //this is not the same as the one in TimeVariant
    //tho it guards the game progress by listening to the global timer signal
    void update();

    //it checks if the game ended. Return true if terminated. Otherwise, false.
    //By calling getGameStatus() to get the terminated reason
    bool checkTerminated();

    QWidget* parent;
    void setParent(QObject *parent); // overload father's setParent to private

    QTime currentTimeLeft;

    QMediaPlayer player{this};
    QMediaPlaylist playlist{this};
signals:
    void notifyAddRedbull();
};

#endif // GAME_H
