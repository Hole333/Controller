TEMPLATE = app

CONFIG += c++11

QT += qml quick serialport

TARGET = CrazyNaN

RESOURCES += Controller.qrc

include(./src/include/include.pri)

HEADERS += \
    $$PWD/src/radiopacket.h \
    $$PWD/src/serialobject.h \
    $$PWD/src/singleton.hpp \
    $$PWD/src/crc.h \
    $$PWD/src/translation.hpp \
    src/simulation.h


SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/radiopacket.cpp \
    $$PWD/src/serialobject.cpp \
    $$PWD/src/crc.cpp \
    src/simulation.cpp

TRANSLATIONS = t1_zh.ts

defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {
        macx {
            DDIR = $${DESTDIR}/$${TARGET}.app/Contents/MacOS
        }
        win32 {
            DDIR = $$DESTDIR
        }

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

win32 {
    RC_ICONS = logo.ico
    system(lrelease t1_zh.ts)
    copyToDestdir($$PWD/t1_zh.qm)
}

macx {
    system(lrelease t1_zh.ts)
    copyToDestdir($$PWD/t1_zh.qm)
}
