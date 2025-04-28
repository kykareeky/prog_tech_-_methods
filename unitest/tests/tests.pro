QT += testlib core network sql
CONFIG += qt console warn_on depend_includepath testcase

SOURCES += \
    ../database.cpp \
    ../dichotomymethod.cpp \
    ../dijkstra.cpp \
    ../functionsforserver.cpp \
    test_database.cpp \
    test_dichotomymethod.cpp \
    test_dijkstra.cpp \
    test_functionsforserver.cpp \
    main.cpp

HEADERS += \
    ../database.h \
    ../dichotomymethod.h \
    ../dijkstra.h \
    ../functionsforserver.h
