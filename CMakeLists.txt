cmake_minimum_required(VERSION 3.10)

project(VK_Metrics_Lib)

set(CMAKE_CXX_STANDARD 17)


set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MetricManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AsyncFileWriter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CPUMetric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/HTTPMetric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(VK_Metrics_Lib ${SOURCES})
target_include_directories(VK_Metrics_Lib PRIVATE ${CMAKE_SOURCE_DIR}/include)