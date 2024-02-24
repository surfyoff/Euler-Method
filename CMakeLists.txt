cmake_minimum_required(VERSION 3.27)
project(euler-method)

list(APPEND CMAKE_PREFIX_PATH "C:\\Packages\\SDL2-2.30.0-VC;C:\\Packages\\SDL2_image-2.8.2-VC;C:\\Packages\\SDL2_ttf-2.22.0-VC")

add_executable(
	${PROJECT_NAME}
	src/main.cpp
	classes/Input/Input.cpp
)

find_package(SDL2 2.30.0 EXACT REQUIRED PATHS C:\\Packages\\SDL2-2.30.0-VC NO_DEFAULT_PATH)
find_package(SDL2_image 2.8.2 EXACT REQUIRED PATHS C:\\Packages\\SDL2_image-2.8.2-VC NO_DEFAULT_PATH)
find_package(SDL2_ttf 2.22.0 EXACT REQUIRED PATHS C:\\Packages\\SDL2_ttf-2.22.0-VC NO_DEFAULT_PATH)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC include/
	PUBLIC classes/Input
	PRIVATE ${SDL2_INCLUDE_DIRS}
	PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS}
	PRIVATE ${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)