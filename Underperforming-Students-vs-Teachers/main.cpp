#include "mainwindow.h"
#include "student.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Student s;
    return a.exec();
}
