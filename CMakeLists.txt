cmake_minimum_required(VERSION 3.16)

project(kbidle VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(openrgb-cppsdk)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)
find_package(KF6IdleTime REQUIRED)
find_package(hidapi REQUIRED)
qt_standard_project_setup()

qt_add_executable(kbidle
    main.cpp
    KBIdleApp.cpp
    KBInterface.cpp
    KBManager.cpp
)

target_include_directories(kbidle PRIVATE openrgb-cppsdk/include)
target_link_libraries(kbidle PRIVATE orgbsdk)

target_link_libraries(kbidle PRIVATE hidapi-hidraw Qt6::Core Qt6::Gui KF6::IdleTime)
