#ifndef ROW_H
#define ROW_H

#include <QObject>
#include <queue>
#include "student.h"
#include "assignment.h"
#include <QVector>
#include "teacher.h"


/***
 * Author: Tse Wai Chung
 * Date: 11/15/2021
 *
 * ---- Description -----
 * A Row Maintains all the objects (Student, Assignment, Teacher) in a row using three heaps and an array.
 * Row provides fast accessors/mutators, but removing specific elements can be expensive.
 * Objects should be created outside, and be added to row only after creation.
 * Row will manage it and delete it properly.
 * Please do not delete objects in a row from outside. It will create serious trouble.
 *
 * !!! - this version has not been proven to be bug-free - !!!
 *
 */

class Row : public QObject
{
    Q_OBJECT
public:

    explicit Row(int size, QObject *parent = nullptr);

    /** RightMost operations **/
    const Student* getRightMostStudent() const;         // returns a const reference of right most student.
    const Assignment* getRightMostAssignment() const;   // returns a const reference of right most assignment.
    Student* popRightMostStudent();               // returns the reference of right most student, and remove it from the row.
    Assignment* popRightMostAssignment();         // returns the reference of right most assignment, and remove it from the row.
    Teacher* popLeftMostTeacher();                      // returns the reference of left most teacher, and remove it from the row.
    void setRightMostStudentHp(int hp);                 // set the Hp of right most student.


    /** Add operations**/
    void addStudent(Student* const s, int pos);         // add a student at certain pos
    void addAssignment(Assignment* const a);            // add an assignment
    void addTeacher(Teacher* const t);                  // add a teacher to the row


    /** Remove operations (! Note: remove according to index is expensive)**/
    void removeStudent(int pos);

    /** Status accessors **/
    bool isEmptyStudent() const;
    bool isEmptyAssignment() const;
    int getNumStudent() const;
    int getNumAssignment() const;
    int getGridSize() const;
    bool hasReachedEnd() const;

    ~Row();

private:

    // Dummy structures for priority comparison
    struct lessStudent {
        bool operator()(const Student* t1, const Student* t2) { //Both students and assignments are TimeVariant
            return t1->getDistanceFromLeft() < t2->getDistanceFromLeft();
        }
    };

    struct lessAssignment {
        bool operator()(const Assignment* t1, const Assignment* t2) { //Both students and assignments are TimeVariant
            return t1->getDistanceFromLeft() < t2->getDistanceFromLeft();
        }
    };

    struct greaterTeacher {
        bool operator()(const Teacher* t1, const Teacher* t2) { //Both students and assignments are TimeVariant
            return t1->getDistanceFromLeft() > t2->getDistanceFromLeft();
        }
    };

    std::priority_queue<Student*, QVector<Student*>, lessStudent> studentQueue;
    std::priority_queue<Assignment*, QVector<Assignment*>, lessAssignment> assignmentQueue;
    std::priority_queue<Teacher*, QVector<Teacher*>, greaterTeacher> teacherQueue;
    //Pointers are used to avoid the const access constriant

    Student** grid; //stores a pointer pointing to each student.
    int grid_size;

    bool inBound(int pos) const;
    void deregisterFromGrid(Student* s);

signals:

};



#endif // ROW_H
