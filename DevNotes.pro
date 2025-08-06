QT += core gui qml quick quickcontrols2 widgets

CONFIG += c++17

TARGET = DevNotes
TEMPLATE = app

# Directory di output
DESTDIR = $$PWD
OBJECTS_DIR = $$PWD/obj
MOC_DIR = $$PWD/obj
RCC_DIR = $$PWD/obj

# File sorgenti
SOURCES += \
    src/main.cpp \
    src/core/ApplicationCore.cpp \
    src/models/DocumentModel.cpp \
    src/models/FileSystemModel.cpp

# File header
HEADERS += \
    src/core/ApplicationCore.h \
    src/models/DocumentModel.h \
    src/models/FileSystemModel.h

# Risorse QML
RESOURCES += resources.qrc

# Configurazioni MinGW
win32 {
    # Configurazione per Windows
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
    CONFIG += console
    
    # Versione
    VERSION = 1.0.0
    QMAKE_TARGET_COMPANY = "Windows Helper Solutions"
    QMAKE_TARGET_PRODUCT = "DevNotes"
    QMAKE_TARGET_DESCRIPTION = "Modern note-taking application inspired by Obsidian"
    QMAKE_TARGET_COPYRIGHT = "2025"
}

# Configurazioni debug/release
CONFIG(debug, debug|release) {
    message("Building in DEBUG mode")
    DEFINES += DEBUG_BUILD
} else {
    message("Building in RELEASE mode")
    DEFINES += QT_NO_DEBUG_OUTPUT
}

# Include path per header personalizzati
INCLUDEPATH += \
    src \
    src/core \
    src/models \
    src/ui
