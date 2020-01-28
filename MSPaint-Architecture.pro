QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AxonometryLineTool.cpp \
    ImageDrawer.cpp \
    LineTool.cpp \
    PencilTool.cpp \
    PerspectiveLineTool.cpp \
    RenderArea.cpp \
    RulerTool.cpp \
    main.cpp \
    imagedrawsize.cpp \
    mainwindow.cpp

HEADERS += \
    AxonometryLineTool.h \
    ImageDrawer.h \
    LineTool.h \
    PencilTool.h \
    PerspectiveLineTool.h \
    RenderArea.h \
    RulerTool.h \
    imagedrawsize.h \
    Tool.h \
    mainwindow.h

FORMS += \
    imagedrawsize.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:\opencv\build\include

LIBS += C:\opencv-build\bin\libopencv_core412.dll
LIBS += C:\opencv-build\bin\libopencv_highgui412.dll
LIBS += C:\opencv-build\bin\libopencv_imgcodecs412.dll
LIBS += C:\opencv-build\bin\libopencv_imgproc412.dll
LIBS += C:\opencv-build\bin\libopencv_features2d412.dll
LIBS += C:\opencv-build\bin\libopencv_calib3d412.dll

RESOURCES += \
    images.qrc
