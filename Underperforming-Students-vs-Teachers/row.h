#ifndef ROW_H
#define ROW_H

#include <QObject>
#include <queue>
#include "student.h"
#include "assignment.h"
#include <QVector>
#include "teacher.h"
#include "game.h"
#include "timevariant.h"

/***
 * Date: 11/15/2021
 *
 * ---- Description -----
 * A Row Maintains all the objects (Student, Assignment, Teacher) in a row using three heaps and an array.
 * Row provides fast accessors/mutators, but removing specific elements can be expensive.
 * Row will manage all generated objects and delete it properly.
 * Please do not delete objects in a row from outside. It will create serious trouble.
 * Also, do not modify the position of objects in a row, it disturbs the internal order of the heap.
 *
 *
 * Update 1 11/15/2021
 * Teachers are now maintained using vector instead of heap
 * added more comments
 */

class Teacher;
class Student;
class Assignment;
class Desmond;

class Row : public QObject
{
    Q_OBJECT

public:
    /*** Coordinates and notes ***/
    /*** A Row looks like this:
     *
     *  | tile 0 | tile 1 | tile 2 | ... | tile Game::NUMBER_OF_COLUMNS-1 |
     *
     *  The left most position is tile 0
     *  The right most position is NUMBER_OF_COLUMNS - 1
     * **/

    Row(int yPos, int size, QWidget *parent = nullptr);

    /** Static Constant Fields **/

    /** RightMost operations **/
    const Student* getRightMostStudent() const;         // returns a const reference of right most student.
    const Assignment* getRightMostAssignment() const;   // returns a const reference of right most assignment.
    Student* popRightMostStudent();               // returns the reference of right most student, and remove it from the row.
    Assignment* popRightMostAssignment();         // returns the reference of right most assignment, and remove it from the row.
    Teacher* getLeftMostTeacher() const;                      // access the leftmost teacher
    void setRightMostStudentHp(int hp);                 // set the Hp of right most student.


    /** Add operations**/
    void addStudent(TimeVariant::Type type, int tile_pos); // create a new student at tile_pos
    void addTeacher(TimeVariant::Type type);            // create a teacher at the right side of the row
    void addAssignment(Student* shooter, int damage,  // create a new assignment at tile_pos with the given pixmap
                       QPixmap pixmap = *Assignment::PIC_0);


    /** Remove operations (! Note: remove according to index is expensive)**/
    void removeStudent(int pos);                        // deregister a student from the row, it will also be deleted.
    void removeTeacher(Teacher* teacher);               // deregister a teacher from the row, it will also be deleted.

    /** Status accessors **/
    bool isEmptyStudent() const;        // whether this row has any student
    bool isEmptyAssignment() const;     // whether this row has any assignment
    int getNumStudent() const;          // how many students are in this row
    int getNumAssignment() const;       // how many assignments are in this row
    int getGridSize() const;            // the size of the grid
    bool hasReachedEnd() const;         // if any teacher has reached the end of this row
    int getYPos() const;                // the y position of the row
    bool hasStudentAt(int pos) const;   //returns true if has student at position pos.

    /** Utilities **/
    void updateLeftMostTeacher();       // A utility function to update the leftmost teacher
    void printTeacherList();            // print all teachers (for debug)
    void modifyTeachers(void (*f)(Teacher* t));
                                        // Provides a way to modify teachers. For safety reasons, function pointer is used.
                                        // We will check if the given function modifies distance parameters (not allowed)

    Student** grid; //stores a pointer pointing to each student.

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

    std::priority_queue<Student*, QVector<Student*>, lessStudent> studentQueue;             //the priority queue maintaining students
    std::priority_queue<Assignment*, QVector<Assignment*>, lessAssignment> assignmentQueue; //the priority queue maintaining assignments
    //Pointers are used to avoid the const access constriant


    QVector<Teacher*> teacherList;  //the list of teachers
    int leftMostTeacherIndex;       //the index of the left most teacher.
    int grid_size;

    bool inBound(int pos) const;
    void deregisterFromGrid(Student* s);
    QLabel* generateQLabelAtPos(int x); //generate a null

    void addStudent(Student* const s, int pos);         // register a student at certain pos
    void addAssignment(Assignment* const a);            // register an assignment
    void addTeacher(Teacher* const t);                  // register a teacher to the row

    int yPos;
    QWidget* parent;

signals:

};

#endif // ROW_H
