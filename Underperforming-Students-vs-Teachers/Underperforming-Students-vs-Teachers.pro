QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attackstudent.cpp \
    cgagod.cpp \
    deadlinefighter.cpp \
    desmond.cpp \
    game.cpp \
    gbusstudent.cpp \
    human.cpp \
    kelvin.cpp \
    main.cpp \
    mainwindow.cpp \
    overworkedta.cpp \
    pang.cpp \
    shamelessstudent.cpp \
    sleepdeprivedstudent.cpp \
    student.cpp \
    supportstudent.cpp \
    teacher.cpp \
    teacherspet.cpp \
    timevariant.cpp

HEADERS += \
    attackstudent.h \
    cgagod.h \
    deadlinefighter.h \
    desmond.h \
    game.h \
    gbusstudent.h \
    human.h \
    kelvin.h \
    mainwindow.h \
    overworkedta.h \
    pang.h \
    shamelessstudent.h \
    sleepdeprivedstudent.h \
    student.h \
    supportstudent.h \
    teacher.h \
    teacherspet.h \
    timevariant.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES +=
