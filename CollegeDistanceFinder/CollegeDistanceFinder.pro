QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    collegedistancewidget.cpp \
    csvparser.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    collegedistancewidget.h \
    csvparser.h \
    loginwindow.h \
    mainwindow.h \

FORMS += \
    collegedistancewidget.ui \
    loginwindow.ui \
    mainwindow.ui \

RESOURCES += \
    resources.qrc \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
