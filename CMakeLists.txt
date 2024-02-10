cmake_minimum_required(VERSION 3.15)

project(data_processor LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/element.h ${CMAKE_SOURCE_DIR}/src/element.cpp
                    ${CMAKE_SOURCE_DIR}/src/input_data.h ${CMAKE_SOURCE_DIR}/src/input_data.cpp
                    ${CMAKE_SOURCE_DIR}/src/output_data.h ${CMAKE_SOURCE_DIR}/src/output_data.cpp
                    ${CMAKE_SOURCE_DIR}/src/settings.h ${CMAKE_SOURCE_DIR}/src/settings.cpp
                    ${CMAKE_SOURCE_DIR}/src/operation.h ${CMAKE_SOURCE_DIR}/src/operation.cpp
                    ${CMAKE_SOURCE_DIR}/src/processor.h ${CMAKE_SOURCE_DIR}/src/processor.cpp
                    ${CMAKE_SOURCE_DIR}/src/solution.h ${CMAKE_SOURCE_DIR}/src/solution.cpp
                    ${CMAKE_SOURCE_DIR}/src/json.h ${CMAKE_SOURCE_DIR}/src/json.cpp
                    ${CMAKE_SOURCE_DIR}/src/reader.h ${CMAKE_SOURCE_DIR}/src/reader.cpp
                    ${CMAKE_SOURCE_DIR}/src/main.cpp  ${CMAKE_SOURCE_DIR}/src/common.h)

add_executable(data_processor src/main.cpp ${PROJECT_SOURCES})
