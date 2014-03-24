#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T23:21:34
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_storagesimple_unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_storagesimple_unittest.cpp ../../storagesimpletext.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

QMAKE_CXXFLAGS += -std=c++11
