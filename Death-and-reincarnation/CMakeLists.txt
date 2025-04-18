cmake_minimum_required(VERSION 3.16)

project(Death-and-reincarnation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ./src/headers/person.h
        ./src/headers/humanity.h
        ./src/headers/world.h
        ./src/headers/angel.h
        ./src/headers/heaven.h
        ./src/headers/graveyard.h
        ./src/cpp/world.cpp
        ./src/cpp/person.cpp
        ./src/cpp/humanity.cpp
        ./src/cpp/graveyard.cpp
        ./src/cpp/angel.cpp
        ./src/cpp/heaven.cpp
        ./src/angelNames
        ./src/names
        ./src/lastNames
        ./src/countries
        ./src/religion
        ./src/majors
        ./src/deathLog
        ./src/humanity
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Death-and-reincarnation
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/headers/person.h
        src/headers/humanity.h
        src/headers/world.h
        src/headers/graveyard.h
        src/headers/heaven.h
        src/headers/angel.h
        src/cpp/world.cpp
        src/cpp/person.cpp
        src/cpp/humanity.cpp
        src/cpp/graveyard.cpp
        src/cpp/angel.cpp
        src/cpp/heaven.cpp

        src/angelNames
        src/names
        src/lastNames
        src/countries
        src/religion
        src/majors
        src/deathLog
        src/humanity
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Death-and-reincarnation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Death-and-reincarnation SHARED
            ${PROJECT_SOURCES}
                main.cpp
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Death-and-reincarnation
            ${PROJECT_SOURCES}
                main.cpp
        )
    endif()
endif()

target_link_libraries(Death-and-reincarnation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Death-and-reincarnation)
endif()
set_target_properties(Death-and-reincarnation PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Death-and-reincarnation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Death-and-reincarnation)
endif()
