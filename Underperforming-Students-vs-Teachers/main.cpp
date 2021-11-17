#include "mainwindow.h"
#include "sleepdeprivedstudent.h"
#include "row.h"
#include "teacher.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //row_test_1(&w);


    return a.exec();
}

/*
void row_test_1(QWidget* w)
{
    QLabel* l = new QLabel();
    // Test 1-1, create a row, and delete it.
    Row* row1 = new Row(10, w);
    delete row1;
    qDebug("Test 1 passed");

    // Test 1-2, create a row, add a few students, and delete it.
    Row* row2 = new Row(10,w);
    for(int i = 0; i < 10; i++) {
        if(i != 7 || i != 3) {
            SleepDeprivedStudent* s = new SleepDeprivedStudent(l);
            row2->addStudent(s, i);
        }
    }

    for(int i = 0; i < 10; i ++) {
        row2->getRightMostStudent()->
    }

    // Test 1-3,

}
*/
