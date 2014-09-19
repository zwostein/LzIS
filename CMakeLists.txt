cmake_minimum_required( VERSION 2.8 )
project( LzIS )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH} )

set( EXECUTABLE_NAME "lzis" )
add_executable( ${EXECUTABLE_NAME}
	src/main.cpp

	src/EventSystem.cpp

	src/Resource/ImageFileLoader.cpp

	src/Model/Updater.cpp

	src/Model/Net/PulseDistributor.cpp
	src/Model/Net/PulseNode.cpp

	src/Model/Station/AStation.cpp
	src/Model/Station/SolarPlant.cpp
	src/Model/Station/Phaser.cpp
	src/Model/Station/Hub.cpp

	src/View/Window/SDL2.cpp

	src/View/Renderer/RendererFactory.cpp

	src/View/Renderer/SDL2/SolarPlantRenderer.cpp
	src/View/Renderer/SDL2/PhaserRenderer.cpp
	src/View/Renderer/SDL2/PulseLinkRenderer.cpp
	src/View/Renderer/SDL2/StationToolbarRenderer.cpp

#	src/View/Renderer/GLES2/SolarPlantRenderer.cpp
#	src/View/Renderer/GLES2/PhaserRenderer.cpp
#	src/View/Renderer/GLES2/PulseLinkRenderer.cpp
	src/View/Renderer/GLES2/StationToolbarRenderer.cpp
	src/View/Renderer/GLES2/Shader.cpp
	src/View/Renderer/GLES2/Program.cpp
	src/View/Renderer/GLES2/Error.cpp
	src/View/Renderer/GLES2/Texture2D.cpp

	src/Controller/StationToolbar.cpp
)

include_directories( "${CMAKE_SOURCE_DIR}/src" )

# configure compiler for c++11 etc.
if( "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11" )
endif()


# wrap the main function for those OSes
if( ${CMAKE_SYSTEM_NAME} MATCHES "^Windows$|^Android$|^Darwin$" )
	set( NEED_MAIN_WRAP TRUE )
endif()

option( ENABLE_SDL2 "Enable SDL2" ON )
if( ENABLE_SDL2 )
	if( NOT EXISTS "${CMAKE_SOURCE_DIR}/external/SDL2/CMakeLists.txt" )
		set( USE_SYSTEM_SDL2_DEFAULT TRUE )
	else()
		message( STATUS "Found local SDL2 in external/SDL2 - Defaulting to NOT use system installation." )
	endif()
	option( USE_SYSTEM_SDL2 "Use system SDL2 installation" ${USE_SYSTEM_SDL2_DEFAULT} )
	if( NOT USE_SYSTEM_SDL2 )
		set( SDL_SHARED FALSE CACHE BOOL "Build a shared version of the library" )
		add_subdirectory( "external/SDL2" )
		include_directories( "${CMAKE_SOURCE_DIR}/external/SDL2/include" )
		target_link_libraries( ${EXECUTABLE_NAME} SDL2-static )
		if( NEED_MAIN_WRAP )
			target_link_libraries( ${EXECUTABLE_NAME} SDL2main )
		endif()
	else()
		find_package( SDL2 REQUIRED )
		include_directories( ${SDL2_INCLUDE_DIR} )
		target_link_libraries( ${EXECUTABLE_NAME} ${SDL2_LIBRARY} )
	endif()
endif()


option( ENABLE_SFML "Enable SFML" OFF )
if( ENABLE_SFML )
	if( NOT EXISTS "${CMAKE_SOURCE_DIR}/external/SFML/CMakeLists.txt" )
		set( USE_SYSTEM_SFML_DEFAULT TRUE )
	else()
		message( STATUS "Found local SFML in external/SFML - Defaulting to NOT use system installation." )
	endif()
	option( USE_SYSTEM_SFML "Use system SFML installation" OFF )
	if( NOT USE_SYSTEM_SFML )
		set( BUILD_SHARED_LIBS FALSE CACHE BOOL "Build shared libraries" )
		add_subdirectory( "external/SFML" )
		include_directories( "${CMAKE_SOURCE_DIR}/external/SFML/include" )
		target_link_libraries( ${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics sfml-audio )
		if( NEED_MAIN_WRAP )
			target_link_libraries( ${EXECUTABLE_NAME} sfml-main )
		endif()
	else()
		if( NEED_MAIN_WRAP )
			find_package( SFML 2 REQUIRED system window graphics network audio main )
		else()
			find_package( SFML 2 REQUIRED system window graphics network audio )
		endif()
		include_directories( ${SFML_INCLUDE_DIR} )
		target_link_libraries( ${EXECUTABLE_NAME} ${SFML_LIBRARIES} )
	endif()
endif()


if( NOT EXISTS "${CMAKE_SOURCE_DIR}/external/glm/CMakeLists.txt" )
	set( USE_SYSTEM_GLM_DEFAULT TRUE )
else()
	message( STATUS "Found local GLM in external/glm - Defaulting to NOT use system installation." )
endif()
option( USE_SYSTEM_GLM "Use system GLM installation" ${USE_SYSTEM_GLM_DEFAULT} )
if( NOT USE_SYSTEM_GLM )
	include_directories( "${CMAKE_SOURCE_DIR}/external/glm/" )
endif()


find_package( FreeImage REQUIRED )
include_directories( ${FREEIMAGE_INCLUDE_PATH} )
target_link_libraries( ${EXECUTABLE_NAME} ${FREEIMAGE_LIBRARIES} )
