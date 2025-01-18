cmake_minimum_required(VERSION 3.14)

project(LightYears
	LANGUAGES CXX
	VERSION 1.0.0
)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIGHT_YEARS_ENGINE_TARGET_NAME lightYearsEngine)
set(LIGHT_YEARS_GAME_TARGET_NAME lightYearsGame)

add_subdirectory(lightyearsEngine)
add_subdirectory(lightyearsGame)

