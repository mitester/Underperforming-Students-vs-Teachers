#include "row.h"
#include "game.h"
#include "teacher.h"

#include "cgagod.h"
#include "gbusstudent.h"
#include "shamelessstudent.h"
#include "sleepdeprivedstudent.h"
#include "deadlinefighter.h"
#include "teacherspet.h"

#include "overworkedta.h"
#include "kelvin.h"
#include "pang.h"
#include "desmond.h"

#include <QDebug>
#include <QObject>

Row::Row(int yPos, int size, QWidget *parent) : yPos(yPos), grid_size(size), QObject(parent), parent(parent)
{
    grid = new Student*[size];
    for(int i = 0; i < size; i++) {
        grid[i] = nullptr;
    }
    updateLeftMostTeacher();
}

/**  --- Right Most Operations ---  **/

const Student* Row::getRightMostStudent() const {
    // const ref is returned because external modification may disturb the internal order of queue, not safe
    if(studentQueue.empty())
        return nullptr;
    return studentQueue.top();
}

const Assignment* Row::getRightMostAssignment() const {
    // const ref is returned because external modification may disturb the internal order of queue, not safe
    if(assignmentQueue.empty())
        return nullptr;
    return assignmentQueue.top();
}

Student* Row::popRightMostStudent() {
    // pop a student will remove it from all records in Row, but will not make it deleted
    if(studentQueue.empty())
        return nullptr;
    Student* s = studentQueue.top();
    studentQueue.pop();
    deregisterFromGrid(s);
    return s;
}

Assignment* Row::popRightMostAssignment() {
    if(assignmentQueue.empty())
        return nullptr;
    Assignment* a = assignmentQueue.top();
    assignmentQueue.pop();
    return a;
}

void Row::setRightMostStudentHp(int hp) {
    Student* s = studentQueue.top();
    s->setHp(hp); // hp is not the priority property, so modifying it is safe.
}


Teacher* Row::getLeftMostTeacher() const {
    if(leftMostTeacherIndex < 0 || leftMostTeacherIndex >= teacherList.size() || teacherList.empty())
        return nullptr;
    else
        return teacherList.at(leftMostTeacherIndex);
}

/**  --- Add Operations ---  **/

void Row::addStudent(TimeVariant::Type type, int tile_pos) {
    Student* s = nullptr;
    QLabel* label = new QLabel(parent);
    switch (type) {
    case TimeVariant::Type::CGA_GOD:
        label->setPixmap(*CgaGod::PIC_0);
        s = new CgaGod(label, this);
        break;
    case TimeVariant::Type::GBUS_STUDENT:
        label->setPixmap(*GbusStudent::PIC_0);
        s = new GbusStudent(label, this);
        break;
    case TimeVariant::Type::SHAMELESS_STUDENT:
        label->setPixmap(*ShamelessStudent::PIC_0);
        s = new ShamelessStudent(label, this);
        break;
    case TimeVariant::Type::SLEEP_DEPRIVED_STUDENT:
        label->setPixmap(*SleepDeprivedStudent::PIC_0);
        s = new SleepDeprivedStudent(label, this);
        break;
    case TimeVariant::Type::TEACHERS_PET:
        label->setPixmap(*TeachersPet::PIC_0);
        s = new TeachersPet(label,this);
        break;
    case TimeVariant::Type::DEADLINE_FIGHTER:
        label->setPixmap(*DeadlineFighter::PIC_0);
        s = new DeadlineFighter(label,this);
        break;
    default:
        qDebug() << "Non student type passed in to addStudent() function";
        delete label;
        return;
    }

    label->setGeometry(Game::GRID_LEFT + Game::GRID_INTERVAL_HORIZONTAL * tile_pos, yPos, Student::SPRITE_WIDTH, Student::SPRITE_HEIGHT);
    label->show();
    Game* game = Game::getInstance();
    addStudent(s, tile_pos); //register student to the grid
    game->registerTimeVariant(s);
}

void Row::addTeacher(TimeVariant::Type type) {
    Game* game = Game::getInstance();
    Teacher* t = nullptr;
    QLabel* label = new QLabel(parent);
    switch(type) {
    case TimeVariant::Type::OVERWORKED_TA:
        label->setPixmap(*OverworkedTA::PIC_0);
        t = new OverworkedTA(label, this);
        break;
    case TimeVariant::Type::KELVIN:
        label->setPixmap(*Kelvin::PIC_0);
        t = new Kelvin(label, this);
        break;
    case TimeVariant::Type::PANG:
        label->setPixmap(*Pang::PIC_0);
        t = new Pang(label, this);
        break;
    case TimeVariant::Type::DESMOND:
        label->setPixmap(*Desmond::PIC_0);
        game->desmond = new Desmond(label, this);
        t = game->desmond;
        break;
    default:
        qDebug() << "Non teacher type passed in to addTeacher() function";
        return;
    }
    label->setGeometry(Game::TEA_GEN_POS, yPos, Teacher::SPRITE_WIDTH, Teacher::SPRITE_HEIGHT);
    if(type == TimeVariant::Type::DESMOND)
        label->setGeometry(Game::TEA_GEN_POS, yPos, Teacher::SPRITE_WIDTH * 1.2, Teacher::SPRITE_HEIGHT * 1.2);
    label->lower();
    label->show();
    addTeacher(t);
    game->registerTimeVariant(t);
}

void Row::addAssignment(Student* shooter, int damage) {
    if(shooter == nullptr) {
        qDebug() << "attempt to add assignment at null tile";
        return ;
    }

    Game* game = Game::getInstance();
    QLabel* label = new QLabel(game->getParent());
    label->setPixmap(*Assignment::PIC_0);
    label->setGeometry(shooter->getDistanceFromLeft() + Student::SPRITE_WIDTH*0.5,
                       yPos + Student::SPRITE_HEIGHT * 0.3, Assignment::SPRITE_WIDTH,
                       Assignment::SPRITE_HEIGHT);


    Assignment* a = new Assignment(label, this, damage);
    addAssignment(a);
    game->registerTimeVariant(a);
    label->show();
}


/**  --- Remove Operations ---  **/

void Row::removeStudent(int pos) {
    // Removal of student at a certain position could potentially destroy the internal struture of the heap.
    // Therefore before removing the student, the entire queue has to be emptyed out
    // After the removal, all students are put back to the queue again.
    // This way can the structure of the queue be not distrubed

    if(!inBound(pos))
        return;

    while(!studentQueue.empty()) { // empty out the queue before removal
        studentQueue.pop();
    }

    for(int i = 0; i < grid_size; i++)
    {
        if(grid[i] != nullptr) {
            if(i == pos) { // at the user given location, delete the student and set the pointer to nullptr
                grid[i]->deleteLater();
                grid[i] = nullptr;
            } else { // otherwise, push the student back to queue
                studentQueue.push(grid[i]);
            }
        }
    }
    //the behaviour of "removing student at pos" rarely happens
}

void Row::removeTeacher(Teacher* t) {
    teacherList.removeOne(t);
    t->deleteLater();
    updateLeftMostTeacher();
}

bool Row::isEmptyStudent() const {
    return studentQueue.empty();
}

bool Row::isEmptyAssignment() const {
    return assignmentQueue.empty();
}

int Row::getNumAssignment() const {
    return assignmentQueue.size();
}

int Row::getNumStudent() const {
    return assignmentQueue.size();
}

int Row::getGridSize() const {
    return grid_size;
}

bool Row::hasReachedEnd() const {
    if(leftMostTeacherIndex < 0 || leftMostTeacherIndex >= teacherList.size() || teacherList.empty())
        return false;
    return teacherList[leftMostTeacherIndex]->getDistanceFromLeft() == 0; // check the leftmost position
}

void Row::printTeacherList() {
    qDebug() << "=== start printing all teacher's location ===";
    for(int i = 0; i < teacherList.size(); i++)
    {
        if(!teacherList[i])
            qDebug() << "A Teacher at: " << teacherList[i]->getDistanceFromLeft();
    }
    qDebug() << "=== pirnt end ===";
}


Row::~Row() {
    delete[] grid;
}

/** Private **/
bool Row::inBound(int pos) const {
    return pos >= 0 && pos < grid_size;
}

//delete a student and remove it from the grid.
void Row::deregisterFromGrid(Student *s) {
    for(int i = 0; i < grid_size; i++) {
        if(grid[i] != nullptr && grid[i] == s) {
            grid[i] = nullptr;
        }
    }
}

void Row::updateLeftMostTeacher() {
    int leftmost = -1;
    int leftmost_val = Game::MAX;
    for(int i = 0; i < teacherList.size(); i++) {
        if(teacherList[i] && teacherList[i]->getDistanceFromLeft() < leftmost_val) {
            leftmost_val = teacherList[i]->getDistanceFromLeft();
            leftmost = i;
        }
    }

    leftMostTeacherIndex = leftmost;
}

void Row::addStudent(Student* const s, int pos) {
    if( !inBound(pos) || s==nullptr || grid[pos]!=nullptr)
        return;

    grid[pos] = s;
    studentQueue.push(s);
}

void Row::addAssignment(Assignment *const a) {
    if(a != nullptr)
        assignmentQueue.push(a);
}

void Row::addTeacher(Teacher *const t) {
    if(t == nullptr)    return;
    teacherList.append(t);
    updateLeftMostTeacher();
}

void Row::modifyTeachers(void (*f)(Teacher *)) {
    for(int i = 0; i < teacherList.size(); i++){
        if(teacherList[i]) {
            f(teacherList[i]);
        }
    }
}

//this function is invalidated
Desmond* Row::getDesmond() const {
    for(int i = 0; i < teacherList.size(); i++) {
        if(teacherList[i] && teacherList[i]->getType() == TimeVariant::Type::DESMOND)
            return nullptr;
    }
    return nullptr;
}

int Row::getYPos() const {
    return yPos;
}

bool Row::hasStudentAt(int pos) const {
    if(inBound(pos))
        return grid[pos] != nullptr;
    qDebug() << "invalid pos passed to hasStudentAt()";
    return false;
}







