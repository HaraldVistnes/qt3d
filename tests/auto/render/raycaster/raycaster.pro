TEMPLATE = app

TARGET = raycaster

QT += 3dcore 3dcore-private 3drender 3drender-private testlib

CONFIG += testcase

SOURCES += tst_raycaster.cpp

include(../../core/common/common.pri)
include(../commons/commons.pri)
