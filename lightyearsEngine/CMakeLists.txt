
add_library(${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/application.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/application.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/core.hpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/world.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/world.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/assetmanager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/assetmanager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/actor.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/actor.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/mathutility.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/mathutility.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/object.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/object.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/physicssystem.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/physicssystem.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/delegate.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/delegate.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/timermanager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/timermanager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/vfx/particle.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vfx/particle.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/gamestage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/gamestage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/waitstage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/waitstage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/entrypoint.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/entrypoint.cpp
	)

target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC include)

include(FetchContent)

set(SFML_LIB_NAME sfml)
FetchContent_Declare(
	${SFML_LIB_NAME}
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG 2.6.0
	GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(${SFML_LIB_NAME})

set(BOX2D_LIB_NAME box2d)
FetchContent_Declare(
	${BOX2D_LIB_NAME}
	GIT_REPOSITORY https://github.com/erincatto/box2d
	GIT_TAG v2.4.1
	GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(${BOX2D_LIB_NAME})

set(SFML_INCLUDED_NAMES
	sfml-graphics;
	sfml-system;
	sfml-window;
	sfml-audio
	)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC ${SFML_INCLUDED_NAMES})

set(BOX2D_INCLUDED_NAMES box2d)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC ${BOX2D_INCLUDED_NAMES})

function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND
			${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:${LIB_NAME}>
			$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

CopyLibToTarget(sfml-graphics ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-audio ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-window ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-system ${LIGHT_YEARS_ENGINE_TARGET_NAME})

CopyLibToTarget(box2d ${LIGHT_YEARS_ENGINE_TARGET_NAME})