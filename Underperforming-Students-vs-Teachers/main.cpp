#include "mainwindow.h"
#include "sleepdeprivedstudent.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::priority_queue<int> abc;
    abc.push(1);
    abc.push(2);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
