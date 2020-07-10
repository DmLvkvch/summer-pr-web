QT -= gui
QT+=core websockets
CONFIG += c++11 console TUFAO1
CONFIG -= app_bundle

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

LIBS += -L$$PWD/../../../opt/mongo-cxx-driver/lib/ -lmongocxx-static
INCLUDEPATH += $$PWD/../../../opt/mongo-cxx-driver/include/mongocxx/v_noabi
LIBS += -L$$PWD/../../../opt/mongo-cxx-driver/lib/ -lbsoncxx-static
INCLUDEPATH += $$PWD/../../../opt/mongo-cxx-driver/include/bsoncxx/v_noabi
LIBS += -L$$PWD/../../../usr/local/lib/ -lmongoc-1.0
INCLUDEPATH += $$PWD/../../../usr/local/include/libmongoc-1.0
LIBS += -L$$PWD/../../../usr/local/lib/ -lbson-1.0
INCLUDEPATH += $$PWD/../../../usr/local/include/libbson-1.0
