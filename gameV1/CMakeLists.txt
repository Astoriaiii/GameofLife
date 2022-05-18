cmake_minimum_required(VERSION 3.22)
project(gameV1 C)

set(CMAKE_C_STANDARD 99)

add_executable(gameV1 main.c game.c game.h file.c)

INCLUDE(FindPkgConfig)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMG REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_MIX REQUIRED SDL2_mixer)

include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2_IMG_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_MIX_INCLUDE_DIRS})

link_directories (${SDL2_LIBRARY_DIRS}
        ${SDL2_IMG_LIBRARY_DIRS}
        ${SDL2_TTF_LIBRARY_DIRS}
        ${SDL2_MIX_LIBRARY_DIRS})

target_link_libraries (gameV1          # 这里改成你自己的项目名称
        ${SDL2_LIBRARIES}
        ${SDL2_IMG_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIX_LIBRARIES})
