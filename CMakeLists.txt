cmake_minimum_required(VERSION 3.10)
project(InfinityGamoku)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

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

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
