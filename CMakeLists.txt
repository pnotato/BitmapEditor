cmake_minimum_required(VERSION 3.31)
project(BMPEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(BMPEditor
    main.cpp
    mainwindow.cpp
    imagefile.cpp
)

target_link_libraries(BMPEditor Qt6::Core Qt6::Gui Qt6::Widgets)

qt_standard_project_setup()