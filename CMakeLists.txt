cmake_minimum_required( VERSION 2.8 )
project( LzIS )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH} )

set( EXECUTABLE_NAME "lzis" )
add_executable( ${EXECUTABLE_NAME}
	src/main.cpp
	src/Model/Updater.cpp
	src/Model/IntervalStepUpdater.cpp
	src/Model/Net/PulseNodeLinker.cpp
	src/Model/Net/PulseDistributor.cpp
	src/Model/Station/Hub.cpp
	src/Model/Station/SolarPlant.cpp
	src/Model/Station/Phaser.cpp
#	src/View/SFML/SolarPlantRenderer.cpp
#	src/View/SFML/PhaserRenderer.cpp
#	src/View/SFML/PulseLinkRenderer.cpp
	src/View/SDL2/SolarPlantRenderer.cpp
	src/View/SDL2/PhaserRenderer.cpp
	src/View/SDL2/PulseLinkRenderer.cpp
)

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
	option( USE_SYSTEM_SDL2 "Use system SDL2 installation" OFF )
	if( NOT USE_SYSTEM_SDL2 )
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

option( USE_SYSTEM_GLM "Use system GLM installation" OFF )
if( NOT USE_SYSTEM_GLM )
	include_directories( "${CMAKE_SOURCE_DIR}/external/glm/" )
endif()
