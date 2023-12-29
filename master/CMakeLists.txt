cmake_minimum_required(VERSION 3.22)
project(master)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)
# set(LIB_DIR ${PROJECT_SOURCE_DIR}/libraries)

# set(JSON_LIB_DIR ${LIB_DIR}/nlohmann)

set(SOURCE_FILES 
    main.cpp
    ${SOURCES_DIR}/network/server.cpp)

set(HEADER_FILES 
        ${HEADERS_DIR}/network/server.hpp 
        ${HEADERS_DIR}/model/error.hpp 
        # ${CMAKE_CURRENT_SOURCE_DIR}/util/ResponseWriter.hpp 
        # ${CMAKE_CURRENT_SOURCE_DIR}/util/Json.hpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/util/ProcessRequest.hpp 
        # ${JSON_LIB_DIR}/json.hpp
        )

include_directories(${PROJECT_NAME} ${HEADERS_DIR}/network/ ${HEADERS_DIR}/model/)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})