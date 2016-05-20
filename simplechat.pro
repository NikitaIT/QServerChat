QT       += core websockets
QT       += gui
QT       += network
TARGET = chatserver
CONFIG   -= console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    chatserver.cpp \
    downloader.cpp

HEADERS += \
    chatserver.h \
    downloader.h

OTHER_FILES += *.html\
                *.css

DISTFILES += \
    jsconnect.js

FORMS +=
