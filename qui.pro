#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T12:55:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET          = qui
TEMPLATE        = app
MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = $$PWD/bin
win32:RC_FILE   = other/main.rc
PRECOMPILED_HEADER  = head.h

INCLUDEPATH     += $$PWD
INCLUDEPATH     += $$PWD/form
INCLUDEPATH     += $$PWD/demo
CONFIG          += qt warn_off
DEFINES         += demo1

SOURCES += main.cpp\    
    form/quiwidget.cpp \
    form/quicreator.cpp \
    form/highlighter.cpp \
    form/panelwidget.cpp \
    form/frmdevice.cpp \
    demo/appinit.cpp \
    demo/sliderbar.cpp \
    demo/navlistview.cpp \
    demo/uidemo1.cpp \
    demo/uidemo2.cpp \
    demo/uidemo3.cpp \
    demo/uidemo4.cpp \
    demo/uidemo5.cpp \
    demo/uidemo6.cpp \
    demo/uidemo7.cpp \
    demo/uidemo8.cpp

HEADERS  += head.h\
    form/quiwidget.h \
    form/quicreator.h \
    form/highlighter.h \
    form/panelwidget.h \
    form/frmdevice.h \
    demo/appinit.h \
    demo/sliderbar.h \
    demo/navlistview.h \
    demo/uidemo1.h \
    demo/uidemo2.h \
    demo/uidemo3.h \
    demo/uidemo4.h \    
    demo/uidemo5.h \
    demo/uidemo6.h \
    demo/uidemo7.h \
    demo/uidemo8.h

FORMS    += \
    form/quicreator.ui \
    form/frmdevice.ui \
    demo/uidemo1.ui \
    demo/uidemo2.ui \
    demo/uidemo3.ui \
    demo/uidemo4.ui \
    demo/uidemo5.ui \
    demo/uidemo6.ui \
    demo/uidemo7.ui \
    demo/uidemo8.ui

RESOURCES += \
    other/qss.qrc \
    other/main.qrc \
    demo/demo.qrc \
    demo/image.qrc
