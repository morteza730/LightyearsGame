
add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/gameApplication.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/gameApplication.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Spaceship/Spaceship.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Spaceship/Spaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/player/playerSpaceship.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/playerSpaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/player/reward.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/reward.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/player/player.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/player.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/player/playerManager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/playerManager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/shooter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/shooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/bulletshooter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/bulletshooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/threeWayShooter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/threeWayShooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/FrontalWiper.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/FrontalWiper.cpp

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

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/vanguardStage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/vanguardStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/twinBlade.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/twinBlade.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/twinBladeStage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/twinBladeStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/hexagon.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/hexagon.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/hexagonStage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/hexagonStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/ufo.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/ufo.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/ufoStage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/ufoStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/chaosStage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/chaosStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/boss.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/boss.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/bossStage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/bossStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/gameplayHUD.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/gameplayHUD.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/mainMenuHUD.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/mainMenuHUD.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/level/gameLevelOne.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/level/gameLevelOne.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/level/mainMenuLevel.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/level/mainMenuLevel.cpp
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