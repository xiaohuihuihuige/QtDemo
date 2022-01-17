#-------------------------------------------------
#
# Project created by QtCreator 2020-07-15T10:05:47
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZoomPicture
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        generalfunc.cpp \
        main.cpp \
        mainwindow.cpp \
        qtopencv.cpp

HEADERS += \
        generalfunc.h \
        mainwindow.h \
        qtopencv.h

FORMS += \
        mainwindow.ui


INCLUDEPATH += $$quote( D:/Program Files/opencv-4.1.0-x64-v15/install/include/opencv2\ )
INCLUDEPATH += $$quote( D:/Program Files/opencv-4.1.0-x64-v15/install/include\ )
 DEPENDPATH += $$quote( D:/Program Files/opencv-4.1.0-x64-v15/install/x64/vc15 )
win32:CONFIG(release, debug|release):\
LIBS += -L'D:/Program Files/opencv-4.1.0-x64-v15/install/x64/vc15/lib/' \
    -lopencv_calib3d410 \
       -lopencv_core410 \
        -lopencv_dnn410 \
 -lopencv_features2d410 \
      -lopencv_flann410 \
    -lopencv_highgui410 \
  -lopencv_imgcodecs410 \
    -lopencv_imgproc410 \
         -lopencv_ml410 \
  -lopencv_objdetect410 \
      -lopencv_photo410 \
  -lopencv_stitching410 \
      -lopencv_video410 \
    -lopencv_videoio410
else:win32:CONFIG(debug, debug|release):\
LIBS += -L'D:/Program Files/opencv-4.1.0-x64-v15/install/x64/vc15/lib/' \
   -lopencv_calib3d410d \
      -lopencv_core410d \
       -lopencv_dnn410d \
-lopencv_features2d410d \
     -lopencv_flann410d \
   -lopencv_highgui410d \
 -lopencv_imgcodecs410d \
   -lopencv_imgproc410d \
        -lopencv_ml410d \
 -lopencv_objdetect410d \
     -lopencv_photo410d \
 -lopencv_stitching410d \
     -lopencv_video410d \
   -lopencv_videoio410d




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
