cmake_minimum_required(VERSION 3.1)

project(wxwidgets_smith)

## Compile as C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Compile with the highest warning level
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

## System dependencies
find_package(wxWidgets REQUIRED COMPONENTS net core base aui std)

## Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

## Declare a C++ executable
add_executable(wxwidgets_smith widgetsApp.cpp widgetsMain.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(wxwidgets_smith ${wxWidgets_LIBRARIES})
