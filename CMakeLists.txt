cmake_minimum_required(VERSION 3.29)
project(Simple_Painter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Simple_Painter main.cpp
        include/mainwindow.h
        include/canvas.h
        src/mainwindow.cpp
        src/canvas.cpp
        include/colorbutton.h
        src/colorbutton.cpp
)

target_link_libraries(Simple_Painter
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)



include_directories(${Simple_Painter_SOURCE_DIR}/include)
