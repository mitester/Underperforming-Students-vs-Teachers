#include "row.h"
#include "overworkedta.h"
#include "game.h"
#include "cgagod.h"
#include "gbusstudent.h"
#include "shamelessstudent.h"
#include "sleepdeprivedstudent.h"
#include "teacher.h"
#include "teacherspet.h"
#include "kelvin.h"
#include "pang.h"
#include "desmond.h"
#include "QDebug"

Row::Row(int yPos, int size, QWidget *parent) : QObject(parent), grid_size(size), yPos(yPos), parent(parent)
{
    grid = new Student*[size];
    updateLeftMostTeacher();
}

/**  --- Right Most Operations ---  **/

const Student* Row::getRightMostStudent() const {
    // const ref is returned because external modification may disturb the internal order of queue, not safe
    return studentQueue.top();
}

const Assignment* Row::getRightMostAssignment() const {
    // const ref is returned because external modification may disturb the internal order of queue, not safe
    return assignmentQueue.top();
}

Student* Row::popRightMostStudent() {
    // pop a student will remove it from all records in Row, but will not make it deleted
    Student* s = studentQueue.top();
    studentQueue.pop();
    deregisterFromGrid(s);
    return s;
}

Assignment* Row::popRightMostAssignment() {
    Assignment* a = assignmentQueue.top();
    assignmentQueue.pop();
    return a;
}

void Row::setRightMostStudentHp(int hp) {
    Student* s = studentQueue.top();
    s->setHp(hp); // hp is not the priority property, so modifying it is safe.
}


Teacher* Row::getLeftMostTeacher() const {
    if(leftMostTeacherIndex < 0 || leftMostTeacherIndex >= teacherList.size())
        return nullptr;
    else
        return teacherList.at(leftMostTeacherIndex);
}

/**  --- Add Operations ---  **/
/***
void addStudent(int tile_pos);                      // create a new student at tile_pos
void addTeacher(TimeVariant::Type type);            // create a teacher at the right side of the row
void addAssignment(int tile_pos);                   // create a new assignment at tile_pos
***/

void Row::addStudent(TimeVariant::Type type, int tile_pos) {
    Student* s = nullptr;
    QLabel* label = new QLabel(parent);
    switch (type) {
    case TimeVariant::Type::CGA_GOD:
        label->setPixmap(QPixmap(":/images/students/stu_cga_0.png"));
        s = new CgaGod(label, this);
        break;
    case TimeVariant::Type::GBUS_STUDENT:
        label->setPixmap(QPixmap(":/images/students/stu_gbus_0.png"));
        s = new GbusStudent(label, this);
        break;
    case TimeVariant::Type::SHAMELESS_STUDENT:
        label->setPixmap(QPixmap(":/images/students/stu_shameless_0.png"));
        s = new ShamelessStudent(label, this);
        break;
    case TimeVariant::Type::SLEEP_DEPRIVED_STUDENT:
        label->setPixmap(QPixmap(":/images/students/stu_cga_0.png"));
        s = new SleepDeprivedStudent(label, this);
        break;
    case TimeVariant::Type::TEACHERS_PET:
        label->setPixmap(QPixmap(":/images/students/stu_pet_0.png"));
        s = new TeachersPet(label,this);
        break;
    default:
        qDebug() << "Non student type passed in to addStudent() function";
        delete label;
        return;
    }

    addStudent(s, tile_pos); //register student to the grid
    label->setGeometry(GRID_LEFT + GRID_INTERVAL * tile_pos, yPos, STD_WIDTH, STD_HEIGHT);
}

void Row::addTeacher(TimeVariant::Type type) {
    Teacher* t = nullptr;
    QLabel* label = new QLabel(parent);
    switch(type) {
    case TimeVariant::Type::OVERWORKED_TA:
        label->setPixmap(QPixmap(":/images/teachers/tea_overworked_ta_0.png"));
        t = new OverworkedTA(label, this);
        break;
    case TimeVariant::Type::KELVIN:
        label->setPixmap(QPixmap(":/images/teachers/tea_kelvin_0.png"));
        t = new Kelvin(label, this);
        break;
    case TimeVariant::Type::PANG:
        label->setPixmap(QPixmap(":/images/teachers/tea_pang_0.png"));
        t = new Pang(label, this);
        break;
    case TimeVariant::Type::DESMOND:
        label->setPixmap(QPixmap(":/images/teachers/tea_desmond_0.png"));
        t = new Desmond(label, this);
        break;
    default:
        qDebug() << "Non teacher type passed in to addTeacher() function";
        return;
    }
    addTeacher(t);
    label->setGeometry(TEA_GEN_POS, yPos, STD_WIDTH, STD_HEIGHT);
}

void Row::addAssignment(int tile_pos) {
    QLabel* label = new QLabel(parent);
    label->setPixmap(QPixmap(":/images/items/item_assignment_0.png"));
    label->setGeometry(GRID_LEFT + GRID_INTERVAL * tile_pos, yPos, ASS_WIDTH, ASS_HEIGHT);
    Assignment* a = new Assignment();
    //TODO Complete add Assignment
    addAssignment(a);
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
                delete grid[i];
                grid[i] = nullptr;
            } else { // otherwise, push the student back to queue
                studentQueue.push(grid[i]);
            }
        }
    }
    //the behaviour of "removing student at pos" rarely happens
}

void Row::removeTeacher(Teacher* t) {
    for(QVector<Teacher*>::iterator i = teacherList.begin(); i != teacherList.end(); i++)
        if(*i == t)
            i = teacherList.erase(i);
    delete t;
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
    double leftmost_val = Game::MAX;
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







