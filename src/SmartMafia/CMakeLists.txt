
cmake_minimum_required(VERSION 3.16)

project(SmartMafia VERSION 0.0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core)
set(CMAKE_AUTOMOC ON)

qt_add_qml_module(SmartMafia
    STATIC
    URI SmartMafia
    VERSION 1.0
    
    SOURCES
        MafiaActions.h
)

target_link_libraries(SmartMafia PRIVATE Qt6::Core)

