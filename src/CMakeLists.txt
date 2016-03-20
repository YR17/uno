file(GLOB SOURCES */*.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-window sfml-system sfml-graphics sfml-network jsoncpp curldll mingw32)