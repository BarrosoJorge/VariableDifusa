cmake_minimum_required(VERSION 3.15)
project(VariableDifusa)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB SOURCES "src/*.cpp" "apps/*.cpp")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(VariableDifusa ${SOURCES} )
target_link_libraries(VariableDifusa ${OpenCV_LIBS})
