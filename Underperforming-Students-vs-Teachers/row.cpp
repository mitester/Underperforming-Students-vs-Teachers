#include "row.h"
#include "overworkedta.h"

Row::Row(double yPos, QObject *parent) : QObject(parent), yPos(yPos)
{

}

const Student* Row::getRightMostStudent() const {
    return studentQueue.top();
}

const Assignment* Row::getRightMostAssignment() const {
    return assignmentQueue.top();
}

void Row::removeRightMostStudent() {
    studentQueue.pop();
}

void Row::removeRightMostAssignment() {
    assignmentQueue.pop();
}

void Row::addStudent(Student* const s) {
    studentQueue.push(s);
}

void Row::addAssignment(Assignment *const a) {
    assignmentQueue.push(a);
}

bool Row::isEmptyStudent() {
    return studentQueue.empty();
}

bool Row::isEmptyAssignment() {
    return assignmentQueue.empty();
}

int Row::getNumAssignment() {
    return assignmentQueue.size();
}

int Row::getNumStudent() {
    return assignmentQueue.size();
}

void Row::generateTeacher(TimeVariant::Type type) {
    switch (type) {
    case TimeVariant::Type::OVERWORKED_TA:
        break;
    case TimeVariant::Type::KELVIN:
        break;
    case TimeVariant::Type::PANG:
        break;
    case TimeVariant::Type::DESMOND:
        break;
    default:
        return;
    }
}





