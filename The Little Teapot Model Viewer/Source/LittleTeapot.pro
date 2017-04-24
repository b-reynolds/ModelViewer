#-------------------------------------------------
#
# Project created by QtCreator 2017-04-18T22:51:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LittleTeapot
TEMPLATE = app
LIBS += opengl32.lib
RC_FILE = thelittleteapot.rc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# DEFINES += QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        frmmain.cpp \
    modelviewer.cpp \
    model.cpp \
    frmabout.cpp

HEADERS  += frmmain.h \
    modelviewer.h \
    model.h \
    frmabout.h

FORMS    += frmmain.ui \
    frmabout.ui

RESOURCES += \
    resources.qrc
