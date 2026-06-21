cmake_minimum_required(VERSION 3.19)
project(univ LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(univ
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    student.h
    student.cpp


    dormitory.h
    dormitory.cpp
    room.h
    room.cpp


)

target_link_libraries(univ
    PRIVATE
        Qt::Core
        Qt::Widgets
)