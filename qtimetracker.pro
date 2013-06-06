# -------------------------------------------------
# Project created by QtCreator 2009-12-31T10:10:55
# -------------------------------------------------
QT += core \
    gui \
    widgets
TARGET = qtimetracker
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    taskdialog.cpp \
    support.cpp
HEADERS += mainwindow.h \
    taskdialog.h \
    support.h
FORMS += mainwindow.ui \
    taskdialog.ui

target.path = /usr/local/bin
INSTALLS += target

RESOURCES += \
    qtimetrackerresourcefile.qrc
