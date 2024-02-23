cmake_minimum_required(VERSION 3.27)
project(euler-method)

list(APPEND CMAKE_PREFIX_PATH "C:\\Packages\\SDL2_image-devel-2.8.2;C:\\Packages\\SDL2_ttf-devel-2.22.0;C:\\Packages\\SDL2-devel-2.30.0")

add_executable(
	${PROJECT_NAME}
	src/main.cpp
	classes/Input/Input.cpp
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC include/
	PUBLIC classes/Input
	PRIVATE ${SDL2_INCLUDE_DIRS}
	PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS}
	PRIVATE ${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image ${SDL_TTF_LIBRARIES})