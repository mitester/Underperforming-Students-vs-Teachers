#ifndef ROW_H
#define ROW_H

#include <QObject>
#include <queue>
#include "student.h"
#include "assignment.h"
#include <QVector>


/***
 * Author: Tse Wai Chung
 * Date: 11/15/2021
 *
 * ---- Description -----
 * Row is a class representing a row of the game map.
 * In the game, each row of the map is independent of other rows. namely, all rows behaves exactly the same and there will be no "inter-row" actions.
 * Hence, Row is extracted as a class. Providing all necessary information/utilities for a row.
 *
 * ---- Mechanism ----
 * The core of Row is two priority queues. One is a student queue while the other is an assignment queue.
 *
 */

class Row : public QObject
{
    Q_OBJECT
public:
    explicit Row(double yPos, QObject *parent = nullptr);

    const Student* getRightMostStudent() const;
    const Assignment* getRightMostAssignment() const;

    void removeRightMostStudent();
    void removeRightMostAssignment();

    void addStudent(Student* const s);
    void addAssignment(Assignment* const a);

    bool isEmptyStudent();
    bool isEmptyAssignment();

    int getNumStudent();
    int getNumAssignment();

    void generateTeacher(TimeVariant::Type a);

private:
    // A Dummy structure for priority comparison
    struct greaterThan {
        bool operator()(const TimeVariant* t1, const TimeVariant* t2) { //Both students and assignments are TimeVariant
            return t1->getDistanceFromLeft() > t2->getDistanceFromLeft();
        }
    };

    std::priority_queue<Student*, QVector<Student*>, greaterThan> studentQueue;
    std::priority_queue<Assignment*, QVector<Assignment*>, greaterThan> assignmentQueue;
    //Pointers are used to avoid the const access constriant

    double y;

signals:

};

#endif // ROW_H
