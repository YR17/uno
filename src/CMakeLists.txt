file(GLOB SOURCES */*.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-window sfml-system sfml-graphics jsoncpp curldll mingw32)