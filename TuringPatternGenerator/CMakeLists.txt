cmake_minimum_required(VERSION 3.16)
project(TuringPatternGenerator LANGUAGES CXX) # CXX means C++ language

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON) # AUTOMOC means automatic handling of Qt's MOC (Meta-Object Compiler)
set(CMAKE_AUTORCC ON) # AUTOMOC means automatic handling of Qt's Resource Compiler
set(CMAKE_AUTOUIC ON) # AUTOMOC means automatic handling of Qt's User Interface Compiler

find_package(Qt6 REQUIRED COMPONENTS Widgets) # Find the Qt6 Widgets module

add_executable(TuringPatternGenerator
    main.cpp
    TuringPatternGenerator.cpp
    TuringPatternGenerator.hpp
    SimCanvas.cpp
    SimCanvas.hpp
    UIPanel.cpp
    UIPanel.hpp
)

target_link_libraries(TuringPatternGenerator PRIVATE Qt6::Widgets) # Link the Qt6 Widgets library to the executable
# The PRIVATE keyword means that the Qt6::Widgets library is only needed for this target and not for any other targets that depend on it.