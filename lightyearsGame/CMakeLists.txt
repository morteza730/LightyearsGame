
add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/gameApplication.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/gameApplication.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Spaceship/Spaceship.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Spaceship/Spaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/player/playerSpaceship.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/playerSpaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/shooter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/shooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/bulletshooter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/bulletshooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/bullet.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/bullet.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/healthComponent.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/healthComponent.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/vfx/explosion.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vfx/explosion.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/enemySpaceship.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/enemySpaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/vanguard.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/vanguard.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/level/gameLevelOne.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/level/gameLevelOne.cpp
	)

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC include)

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME})

function(CopyLibDirToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND
			${CMAKE_COMMAND} -E copy_directory
			$<TARGET_FILE_DIR:${LIB_NAME}>
			$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

CopyLibDirToTarget(${LIGHT_YEARS_ENGINE_TARGET_NAME} ${LIGHT_YEARS_GAME_TARGET_NAME})

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME})

add_custom_command(
	TARGET ${LIGHT_YEARS_GAME_TARGET_NAME}
	POST_BUILD
	COMMAND
		${CMAKE_COMMAND} -E copy_directory
		${RESOURCE_SRC_DIR}
		$<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
)

configure_file(
	"config.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)