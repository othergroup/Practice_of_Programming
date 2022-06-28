QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    folder_dialog.cpp \
    item_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    display_dialog.cpp \
    DesktopSprite.cpp \
    Sprite.cpp

HEADERS += \
    folder_dialog.h \
    item_dialog.h \
    mainwindow.h \
    display_dialog.h \
    DesktopSprite.h \
    Sprite.h

FORMS += \
    folder_dialog.ui \
    item_dialog.ui \
    mainwindow.ui \
    display_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources.qrc

DISTFILES +=


