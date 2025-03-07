QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    models/campus.cpp \
    models/souvenir.cpp \
    models/user.cpp \
    utils/animatedbackground.cpp \
    utils/csvhandler.cpp \
    utils/custombackground.cpp \
    utils/dbmanager.cpp \
    utils/souvenirtripmanager.cpp \
    views/adminpanel.cpp \
    views/homewindow.cpp \
    views/loginwindow.cpp \
    views/mainwindow.cpp

HEADERS += \
    models/campus.h \
    models/souvenir.h \
    models/user.h \
    utils/animatedbackground.h \
    utils/csvhandler.h \
    utils/custombackground.h \
    utils/dbmanager.h \
    utils/souvenirtripmanager.h \
    views/adminpanel.h \
    views/homewindow.h \
    views/loginwindow.h \
    views/mainwindow.h

FORMS += \
    views/adminpanel.ui \
    views/homewindow.ui \
    views/loginwindow.ui \
    views/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

# Add this line to include the images directory
OTHER_FILES += \
    images/background.jpg

# Include CSV data files
DISTFILES += \
    data/colleges.csv \
    data/souvenirs.csv
