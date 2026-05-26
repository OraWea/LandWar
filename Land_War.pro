QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    blocksssss.cpp \
    main.cpp \
    Land_War.cpp \
    manager.cpp \
    player_land.cpp \
    setting.cpp \
    sprite.cpp \
    thefight.cpp \
    weapons.cpp

HEADERS += \
    Land_War.h \
    blocksssss.h \
    entity.h \
    manager.h \
    player_land.h \
    setting.h \
    sprite.h \
    thefight.h \
    weapons.h

FORMS += \
    Land_War.ui \
    setting.ui \
    thefight.ui

TRANSLATIONS += \
    Land_War_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    image.qrc \
    images.qrc \
    images.qrc \
    images.qrc
