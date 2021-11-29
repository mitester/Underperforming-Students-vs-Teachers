/***
* It guards the whole game
* It is the central game manager
* This class is a singleton class since only one game object is allowed for each game
* copy constructor & operator=() are explicitly deleted
*/
#ifndef GAME_H
#define GAME_H

#include "timevariant.h"
#include "teacher.h"
#include "row.h"
#include "redbull.h"

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
                                                    //emit one timeout() signal per BASIC_TIME_UNIT

    static const int DEFAULT_REDBULL_NUMBER{30};    // it is the default redbull number at the start
    static const int NUMBER_OF_ROW{5};              // it is the number of row of the map
    static const int NUMBER_OF_COLUMN{9};           // it is the number of column of the map
    static const int MAX{INT_MAX};                  // the maximum integer

    const static int GRID_UP {30};                  // it is the y-coordinate of the upper border of the grid
    const static int GRID_DOWN {625};               // it is the y-coordinate of the lower border of the grid

    // the horizontal and vertical interval between two tiles
    const static int GRID_INTERVAL_VERTICAL {115};
    const static int GRID_INTERVAL_HORIZONTAL {97};

    const static int GRID_LEFT {280};        // the position of the leftmost tile
    const static int GRID_RIGHT {1200};         // the position of the rightmost tile
    const static int TEA_GEN_POS {1200};     // the generation position of teachers
    const static int TEA_END_POS {95};       // the end position of teachers (reached this point implies teacher victory)

    const static int GAME_ENDED_LABEL_X{300}; //x-coordinate of the game ended label should show up
    const static int GAME_ENDED_LABEL_Y{100}; //y-coordinate of the game ended label should show up
    const static int GAME_ENDED_LABEL_WIDTH{896};   //width of the game ended label
    const static int GAME_ENDED_LABEL_HEIGHT{504};  //height of the game ended label
    static QPixmap* GAME_SCENE_FAIL;                //picture pointer of the fail label
    static QPixmap* GAME_SCENE_PASS;                //picture pointer of the pass label
    const static int GAME_DURATION{180000};         //game duration in msecs
    Desmond* desmond = nullptr;                     //stores the ref of Desmond
    int desmondRowId = -1;                            //stores the row Desmond in

    static QPoint REDBULL_POS;                      //coordinates of the redbull UI label (every Redbull needs to fly after clicked)
//    const static int SPRITE_HEIGHT {128};
//    const static int SPRITE_WIDTH {100};
//    const static int ASS_HEIGHT {37};
//    const static int ASS_WIDTH {45};

    static QSize currentSize; //save the window size
    static void move(QWidget* w, double xPercent, double yPercent);   //move a QWidget to the correspond absolute position given relative position
    //How to use: pass in (w, 10, 15.7) means move w, 10% and 15.7%

    enum class GameStatus {STUDENT_WON, TEACHER_WON, BATTLING, PAUSED};

    //get instance with its parent
    static Game* getInstance(QWidget* parent = nullptr);

    //save the current selected card info
    TimeVariant::Type selectedSprite = TimeVariant::Type::EMPTY;
    SpriteCard* selectedCard = nullptr;

    //getter and setter of redbullNum
    int getRedbullNum() const;
    bool addRedbull(int n = Redbull::DEFAULT_ENERGY); //default value of n is 1. Decrease it by passing a negative value
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

    //player plays bgm
    QMediaPlayer player{this};

    //the label shows the preview location of the selected sprite card
    QLabel* transLabel = nullptr;

    //it manages the Ui stack position of h
    void adjustHumanLayer(Human* h, int rowId);

private:
    //private constructor, since it's a singleton class
    //copy constructor & operator= are explicitly deleted
    explicit Game(QWidget* parent = nullptr);
    Game(Game& game) = delete;
    void operator=(const Game&) = delete;
    ~Game();

    // save the only Game instance
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
                                     // not allow outsiders to change the parent

    QTime currentTimeLeft; //stores how much time the player still has

    QWidget* sentinels[NUMBER_OF_ROW - 1]; //human stack management layer splits

signals:
    void notifyAddRedbull();
};

#endif // GAME_H
