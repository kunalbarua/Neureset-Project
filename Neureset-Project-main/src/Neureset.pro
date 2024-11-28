QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PC.cpp \
    SineWave.cpp \
    filemanager.cpp \
    headset.cpp \
    main.cpp \
    mainwindow.cpp \
    neureset.cpp \
    probe.cpp \
    sessionmanager.cpp \
    waveformgenerator.cpp

HEADERS += \
    PC.hpp \
    SineWave.hpp \
    filemanager.hpp \
    headset.hpp \
    mainwindow.hpp \
    neureset.hpp \
    probe.hpp \
    sessionmanager.hpp \
    waveformgenerator.hpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
