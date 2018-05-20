cmake_minimum_required(VERSION 3.10)
project(InfinityGamoku)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)

set(SOURCES
        source/Cell.cpp
        source/main.cpp
        source/FieldSector.cpp
        source/GamokuField.cpp
        source/GameView.cpp
        )

set(HEADERS
        include/GamokuCommon.h
        include/Cell.h
        include/FieldSector.h
        include/GamokuField.h
        include/GameView.h
        )


add_executable(InfinityGamoku ${SOURCES} ${HEADERS})
target_include_directories(InfinityGamoku PUBLIC include)