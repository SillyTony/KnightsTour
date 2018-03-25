TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tile.cpp \
    chessboard.cpp \
    knight.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    tile.h \
    chessboard.h \
    knight.h \
    node.h \
    nodequ.h \
    stack.h \
    queue.h

