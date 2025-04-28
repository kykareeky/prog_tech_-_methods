QT -= gui
QT += core
QT += network
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

INCLUDEPATH += /usr/include/openssl
LIBS += -lssl -lcrypto

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    aes.cpp \
    dichotomymethod.cpp \
    database.cpp \
    dijkstra.cpp \
    functionsforserver.cpp \
    main.cpp \
    sha512.cpp \
    tcpserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    aes.h \
    dichotomymethod.h \
    database.h \
    dijkstra.h \
    functionsforserver.h \
    sha512.h \
    tcpserver.h





