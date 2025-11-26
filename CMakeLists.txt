cmake_minimum_required(VERSION 3.15)
project(VariableDifusa)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include
                    pipeline)
file(GLOB SOURCES "src/*.cpp" "apps/*.cpp")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(SOURCES
    src/ConjuntoDifuso.cpp
    src/Premisa.cpp
    src/Regla.cpp
    src/SistemaDifuso.cpp
    src/Trapezoidal.cpp
    src/Triangular.cpp
    src/VariableDifusa.cpp

    pipeline/reader.cpp
)

# --- Ejecutables ---
add_executable(VariableDifusa apps/main.cpp ${SOURCES})
add_executable(VariableDifusa2 apps/main_1.cpp ${SOURCES})   # si tienes otro main

# --- Linking ---
target_link_libraries(VariableDifusa ${OpenCV_LIBS})
target_link_libraries(VariableDifusa2 ${OpenCV_LIBS})
