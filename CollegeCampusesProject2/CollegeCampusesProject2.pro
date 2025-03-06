QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    models/campus.cpp \
    models/souvenir.cpp \
    models/user.cpp \
    utils/campusmanager.cpp \
    utils/csvhandler.cpp \
    utils/custombackground.cpp \
    utils/dbmanager.cpp \
    utils/souvenirmanager.cpp \
    utils/animatedbackground.cpp \
    utils/souvenirtripmanager.cpp \
    views/addcollegedialog.cpp \
    views/adminpanel.cpp \
    views/homewindow.cpp \
    views/hometabwidget.cpp \
    views/loginwindow.cpp \
    views/mainwindow.cpp

HEADERS += \
    models/campus.h \
    models/souvenir.h \
    models/user.h \
    utils/campusmanager.h \
    utils/csvhandler.h \
    utils/custombackground.h \
    utils/dbmanager.h \
    utils/souvenirmanager.h \
    utils/animatedbackground.h \
    utils/souvenirtripmanager.h \
    views/addcollegedialog.h \
    views/adminpanel.h \
    views/homewindow.h \
    views/hometabwidget.h \
    views/loginwindow.h \
    views/mainwindow.h

FORMS += \
    views/mainwindow.ui \
    views/loginwindow.ui \
    views/adminpanel.ui \
    views/homewindow.ui \
    views/addcollegedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

# Add this line to include the images directory
OTHER_FILES += \
    images/background.jpg
