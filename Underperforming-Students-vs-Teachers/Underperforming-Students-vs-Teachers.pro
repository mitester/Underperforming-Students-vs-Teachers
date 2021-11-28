QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    assignment.cpp \
    attackstudent.cpp \
    cgagod.cpp \
    clickablelabel.cpp \
    deadlinefighter.cpp \
    desmond.cpp \
    game.cpp \
    gamewindow.cpp \
    gbusstudent.cpp \
    human.cpp \
    item.cpp \
    kelvin.cpp \
    main.cpp \
    mainwindow.cpp \
    overworkedta.cpp \
    pang.cpp \
    redbull.cpp \
    row.cpp \
    shamelessstudent.cpp \
    sleepdeprivedstudent.cpp \
    spritecard.cpp \
    student.cpp \
    supportstudent.cpp \
    teacher.cpp \
    teacherspet.cpp \
    timevariant.cpp \
    vendingmachine.cpp

HEADERS += \
    assignment.h \
    attackstudent.h \
    cgagod.h \
    clickablelabel.h \
    deadlinefighter.h \
    desmond.h \
    game.h \
    gamewindow.h \
    gbusstudent.h \
    human.h \
    item.h \
    kelvin.h \
    mainwindow.h \
    overworkedta.h \
    pang.h \
    redbull.h \
    row.h \
    shamelessstudent.h \
    sleepdeprivedstudent.h \
    spritecard.h \
    student.h \
    supportstudent.h \
    teacher.h \
    teacherspet.h \
    timevariant.h \
    vendingmachine.h

FORMS += \
    gamewindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    images.qrc \
    sounds.qrc
