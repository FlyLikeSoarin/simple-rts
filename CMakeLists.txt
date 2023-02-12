cmake_minimum_required(VERSION 3.23)
project(sfml_playground)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(SFML)
set(CMAKE_OSX_ARCHITECTURES "arm64")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB sfml_playground_src "source/*.cpp")
message(${sfml_playground_src})
add_executable(sfml_playground ${sfml_playground_src})

target_include_directories(sfml_playground PUBLIC SFML/include)

link_directories(sfml_playground PUBLIC SFML/lib)
target_link_libraries(
    sfml_playground
    PUBLIC
    sfml-window
    sfml-system
    sfml-network
    sfml-graphics
    sfml-audio
)
