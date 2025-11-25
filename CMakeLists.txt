cmake_minimum_required(VERSION 3.16)

project(web3-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


cmake_policy(SET CMP0167 NEW)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)

if(NOT CMAKE_CONFIGURATION_TYPES)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
    endif()
endif()

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

add_subdirectory(submodule/json-rpc)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(web3-cpp
    ${SRC_FILES}
)

target_include_directories(web3-cpp PRIVATE
    include/web3
    submodule/json-rpc/include

)

target_link_libraries(web3-cpp PRIVATE
    nlohmann_json::nlohmann_json
    CURL::libcurl
)
