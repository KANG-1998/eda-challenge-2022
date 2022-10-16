if(DEBUG_IRT_SRC)            
    message(STATUS "RT: DEBUG_IRT_API")       
    set(CMAKE_BUILD_TYPE "Debug")
else()
    message(STATUS "RT: RELEASE_IRT_API")   
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_library(irt_router
    ${IRT_SRC}/Router.cpp
    ${IRT_SRC}/data_manager/DataManager.cpp
    ${IRT_SRC}/logger/Logger.cpp
)


target_link_libraries(irt_router
    PRIVATE
)

target_include_directories(irt_router
    PUBLIC
        ${IRT_SRC}
        ${IRT_SRC}/data_manager
        ${IRT_SRC}/logger
        ${IRT_SRC}/util
)
