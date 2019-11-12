cmake_minimum_required(VERSION 2.6)

project ("demo_sdl2" LANGUAGES C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
# find_package(SDL2_gfx REQUIRED)

# target_link_libraries(demo SDL2 SDL2_image SDL2_ttf)

#add_library(hashi ../src/game.c ../src/node.c)

add_executable(model main.c model.c ../src/init_game.c)
target_link_libraries(model
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_TTF_LIBRARY}
	hashi)

# target_link_libraries(model SDL2 SDL2_image SDL2_ttf)

