cmake_minimum_required(VERSION 3.10)
project(lastfm_client)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rd/poco)

set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/3rd/opencv")
find_package(OpenCV REQUIRED)

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(lastfm-top-albums
    src/main.cpp
    src/http_client.cpp
    src/lastfm_client.cpp
    src/image_utils.cpp
)

target_link_libraries(lastfm-top-albums
    Poco::Foundation
    Poco::Net
    Poco::Util
    Poco::JSON
    ${OpenCV_LIBS}
)
