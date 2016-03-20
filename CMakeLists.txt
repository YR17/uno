project(Uno)
cmake_minimum_required (VERSION 2.6) 

include_directories(include)


find_package(SFML REQUIRED window system graphics network)
include_directories(${SFML_INCLUDE_DIR})
find_package(JSONCPP REQUIRED)
include_directories(${JSONCPP_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-std=c++11 -lws2_32 -lwsock32")
# -static-libgcc -static-libstdc++")
file(MAKE_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
 add_subdirectory(src)

