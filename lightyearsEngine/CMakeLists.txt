set(SFML_LIBRARY_NAMES
	sfml-graphics;
	sfml-system;
	sfml-window;
	sfml-audio
	)

add_library(${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/application.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/application.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/core.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/core.cpp
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
	${CMAKE_CURRENT_SOURCE_DIR}/include/entrypoint.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/entrypoint.cpp
	)

target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC include)

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC ${SFML_LIBRARY_NAMES})

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
