#include "row.h"
#include "overworkedta.h"
#include "game.h"

const QString Row::dummy = "dummy";

Row::Row(int size, QObject *parent) : QObject(parent), grid_size(size)
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
    if(leftMostTeacherIndex < 0 || leftMostTeacherIndex >= teacherList.size())
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






