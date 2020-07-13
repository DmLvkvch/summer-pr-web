QT       -= gui
QT += network

CONFIG += c++11 console TUFAO1

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
        database.cpp \
        main.cpp \
        telegrambot.cpp \
        vkmanager.cpp \
        vkpost.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -ltgbot
unix|win32: LIBS += -ljsoncpp
unix|win32: LIBS += -lcurl

HEADERS += \
    database.h \
    telegrambot.h \
    vkmanager.h \
    vkpost.h

LIBS+=$$PWD/vk.so
INCLUDEPATH+=$$PWD/



unix:!macx: LIBS += -L$$PWD/../../../mongo-cxx-driver/src/mongocxx/ -lmongocxx

INCLUDEPATH += $$PWD/../../../mongo-cxx-driver/src
DEPENDPATH += $$PWD/../../../mongo-cxx-driver/src

unix:!macx: LIBS += -L$$PWD/../../../mongo-cxx-driver/src/bsoncxx/ -lbsoncxx

INCLUDEPATH += $$PWD/../../../mongo-cxx-driver/src
DEPENDPATH += $$PWD/../../../mongo-cxx-driver/src

INCLUDEPATH += $$PWD/../../../mongo-cxx-driver/install/include/bsoncxx/v_noabi
DEPENDPATH += $$PWD/../../../mongo-cxx-driver/install/include/bsoncxx/v_noabi
