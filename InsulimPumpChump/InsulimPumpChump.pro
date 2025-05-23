QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bolus.cpp \
    createprofile.cpp \
    home.cpp \
    main.cpp \
    mainwindow.cpp \
    options.cpp \
    profile.cpp \
    profileeditor.cpp \
    profilemanager.cpp \
    profilepage.cpp

HEADERS += \
    bolus.h \
    createprofile.h \
    def.h \
    home.h \
    mainwindow.h \
    options.h \
    profile.h \
    profileeditor.h \
    profilemanager.h \
    profilepage.h

FORMS += \
    bolus.ui \
    createprofile.ui \
    home.ui \
    mainwindow.ui \
    options.ui \
    profileeditor.ui \
    profilepage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    InsulimPumpChump.pro.user
