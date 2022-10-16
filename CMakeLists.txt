cmake_minimum_required(VERSION 3.11)
project(iRouter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(IRT_API ${PROJECT_SOURCE_DIR}/api)
set(IRT_SRC ${PROJECT_SOURCE_DIR}/src)
set(IRT_TEST ${PROJECT_SOURCE_DIR}/test)

## cmake debug
set(DEBUG_IRT_API ON)
set(DEBUG_IRT_SRC ON)

## build
add_subdirectory(${IRT_API})
add_subdirectory(${IRT_SRC})

include_directories(${IRT_TEST})

## executable file
add_executable(run_router ${IRT_TEST}/test.cpp)

target_link_libraries(run_router
    irt_router
)

