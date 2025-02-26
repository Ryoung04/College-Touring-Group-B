QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    models/campus.cpp \
    models/user.cpp \
    utils/dbmanager.cpp \
    utils/csvhandler.cpp \
    views/loginwindow.cpp \
    views/hometabwidget.cpp \
    views/adminpanel.cpp \
    views/addcollegedialog.cpp

HEADERS += \
    mainwindow.h \
    models/campus.h \
    models/user.h \
    utils/dbmanager.h \
    utils/csvhandler.h \
    views/loginwindow.h \
    views/hometabwidget.h \
    views/adminpanel.h \
    views/addcollegedialog.h

FORMS += \
    mainwindow.ui \
    views/loginwindow.ui \
    views/adminpanel.ui \
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
