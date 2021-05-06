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
    main.cpp \
    mainwindow.cpp\
    recognizelib/train/ann_train.cpp \
    recognizelib/train/annCh_train.cpp \
    recognizelib/train/create_data.cpp \
    recognizelib/train/svm_train.cpp \
    recognizelib/train/train.cpp \
    recognizelib/util/kv.cpp \
    recognizelib/util/program_options.cpp \
    recognizelib/util/util.cpp \
    recognizelib/core/chars_identify.cpp \
    recognizelib/core/chars_recognise.cpp \
    recognizelib/core/chars_segment.cpp \
    recognizelib/core/core_func.cpp \
    recognizelib/core/feature.cpp \
    recognizelib/core/params.cpp \
    recognizelib/core/plate_detect.cpp \
    recognizelib/core/plate_judge.cpp \
    recognizelib/core/plate_locate.cpp \
    recognizelib/core/plate_recognize.cpp \
    recognizelib/thirdparty/LBP/helper.cpp \
    recognizelib/thirdparty/LBP/lbp.cpp \
    recognizelib/thirdparty/mser/mser2.cpp \
    recognizelib/thirdparty/svm/corrected_svm.cpp \
    recognizelib/thirdparty/textDetect/erfilter.cpp \
    recognizelib/thirdparty/xmlParser/xmlParser.cpp

HEADERS += \
    mainwindow.h\
    recognizelib/easypr.h \
    recognizelib/thirdparty/LBP/helper.hpp \
    recognizelib/thirdparty/LBP/lbp.hpp \
    recognizelib/thirdparty/mser/mser2.hpp \
    recognizelib/thirdparty/svm/precomp.hpp \
    recognizelib/thirdparty/textDetect/erfilter.hpp \
    recognizelib/thirdparty/xmlParser/xmlParser.h


FORMS += \
    mainwindow.ui


INCLUDEPATH +=$$PWD/recognizelib #添加识别训练头文件路径

INCLUDEPATH += /home/gec/install/include
LIBS +=        /home/gec/install/lib/libopencv_*

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
