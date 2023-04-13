cmake_minimum_required(VERSION 3.21)
project(raycast C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} include)

add_executable(raycast
        src/main.c
        src/raycast.c
        src/map.c
        src/minimap.c
        src/asset.c
        src/render.c
        src/world.c
        )

target_link_libraries(raycast PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
