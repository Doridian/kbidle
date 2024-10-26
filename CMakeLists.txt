cmake_minimum_required(VERSION 3.16)

project(kbidle VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)
find_package(KF6IdleTime REQUIRED)
qt_standard_project_setup()

qt_add_executable(kbdidle
    main.cpp
    KBIdleApp.cpp
)

target_link_libraries(kbdidle PRIVATE Qt6::Core Qt6::Gui KF6::IdleTime)
