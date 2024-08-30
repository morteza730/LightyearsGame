set(LIGHT_YEARS_GAME_TARGET_NAME lightYearsGame)

add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	)

set(SFML_LIBRARY_NAMES
	sfml-graphics;
	sfml-system;
	sfml-window;
	sfml-audio
	)

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${SFML_LIBRARY_NAMES})