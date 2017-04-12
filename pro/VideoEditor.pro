include ( ../resources/pythonQtConsole/common.prf ) 

QT += core gui widgets sql

TARGET = VideoEditor
TEMPLATE = app

CONFIG += qt
CONFIG += no_keywords

QMAKE_CXXFLAGS += -g -std=c++11 -pedantic -Werror -Wall

OBJ_DIR = ../build
OBJECTS_DIR = ../build
MOC_DIR = ../build
DESTDIR = ../bin
INCLUDEDIR=../include
SRCDIR=../src
UI_DIR = ../include

SOURCES +=	$$SRCDIR/video.cpp \
		$$SRCDIR/videos.cpp \
		$$SRCDIR/main.cpp \
		$$SRCDIR/mainwindow.cpp \
		$$SRCDIR/listwidget.cpp \
	$$SRCDIR/frame.cpp 
			

HEADERS +=	$$INCLUDEDIR/video.h \
		$$INCLUDEDIR/videos.h \
	$$INCLUDEDIR/mainwindow.h \
 $$INCLUDEDIR/listwidget.h \
 $$INCLUDEDIR/frame.h

INCLUDEPATH +=./$${INCLUDEDIR} ../resources/pythonQtConsole/include /usr/include/x86_64-linux-gnu/libavcodec/ /usr/include/x86_64-linux-gnu/libavformat/ /usr/include/ffmpeg

LIBS +=-lboost_system -lboost_filesystem  -L/usr/lib/x86_64-linux-gnu/ -lswscale -lavcodec -lavformat -lavutil  -lz -lavutil -lm -L../resources/pythonQtConsole/lib -lpythonQtConsole 

FORMS    += ../ui/mainwindow.ui

