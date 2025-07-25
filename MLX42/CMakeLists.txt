# -----------------------------------------------------------------------------
# Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
# See README in the root project for more information.
# -----------------------------------------------------------------------------

# CMake specifications
# -----------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.16.0)

# Explicitly disable C++ and only enable C
project(mlx42 VERSION 2.4.1 LANGUAGES C)
set(CMAKE_CXX_COMPILER_WORKS 0)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

message(STATUS "MLX42 @ ${CMAKE_PROJECT_VERSION}")

# Variables
# -----------------------------------------------------------------------------
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TOOLS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Force C compilation for all files
set(CMAKE_C_COMPILER_FORCED TRUE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Force .cc files to be treated as C source files
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "")
set_property(GLOBAL PROPERTY C_COMPILE_OBJECT "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
set(CMAKE_CC_COMPILER ${CMAKE_C_COMPILER})

# Options
set(DEBUG		OFF CACHE BOOL "Build MLX42 in debug mode, enabling assertions")
set(GLFW_FETCH	ON CACHE BOOL "Clone and install GLFW")
set(BUILD_TESTS	OFF CACHE BOOL "Build the tests to verify the integrity of the lib")

# Compile Options
# -----------------------------------------------------------------------------

# Reduce the size of LodePNG, we don't need these things.
add_definitions(-D LODEPNG_NO_COMPILE_ENCODER)
add_definitions(-D LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS)

if(UNIX AND NOT EMSCRIPTEN)
	add_compile_options(
		-Wextra
		-Wall
		-Wunreachable-code

		# Some low priority warnings that are annoying.
		-Wno-char-subscripts
		-Wno-sign-compare
		-Wno-unused-parameter
		-Wno-missing-field-initializers
		
		# C-specific options
		-Wno-incompatible-pointer-types
		-Wno-int-conversion
	)
	if(DEBUG)
		message(STATUS "Building in DEBUG mode")
		add_compile_options(-g)
	else()
		message(STATUS "Building in RELEASE mode")
		add_definitions(-D NDEBUG)
		add_compile_options(-O2)
	endif(DEBUG)
else()
	# TODO: Figure out what we need for windows.
endif()

# Build specific files
# @see https://cmake.org/cmake/help/latest/command/add_custom_command.html
# -----------------------------------------------------------------------------

if (UNIX)
	set(CCSHADER ${TOOLS_DIR}/compile_shader.sh)
else()
	set(CCSHADER ${TOOLS_DIR}/compile_shader.bat)
endif()

if(EMSCRIPTEN)
	set(EMSCRIPTEN_VALUE 1)
else()
	set(EMSCRIPTEN_VALUE 0)
endif()

# Add custom command for fragment shader
add_custom_command(
	COMMENT "Building fragment shader"
	DEPENDS ${PROJECT_SOURCE_DIR}/shaders/default.frag
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mlx_frag_shader.cc
	COMMAND ${CCSHADER} ${PROJECT_SOURCE_DIR}/shaders/default.frag ${EMSCRIPTEN_VALUE} > ${CMAKE_CURRENT_BINARY_DIR}/mlx_frag_shader.cc
	VERBATIM
	USES_TERMINAL
)

# Add custom command for vertex shader
add_custom_command(
	COMMENT "Building vertex shader"
	DEPENDS ${PROJECT_SOURCE_DIR}/shaders/default.vert
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mlx_vert_shader.cc
	COMMAND ${CCSHADER} ${PROJECT_SOURCE_DIR}/shaders/default.vert ${EMSCRIPTEN_VALUE} > ${CMAKE_CURRENT_BINARY_DIR}/mlx_vert_shader.cc
	VERBATIM
	USES_TERMINAL
)

# Sources
# -----------------------------------------------------------------------------

# Collect all source files
set(MLX42_SOURCES
	# Root
	${SOURCE_DIR}/mlx_cursor.cc
	${SOURCE_DIR}/mlx_exit.cc
	${SOURCE_DIR}/mlx_images.cc
	${SOURCE_DIR}/mlx_init.cc
	${SOURCE_DIR}/mlx_keys.cc
	${SOURCE_DIR}/mlx_loop.cc
	${SOURCE_DIR}/mlx_monitor.cc
	${SOURCE_DIR}/mlx_mouse.cc
	${SOURCE_DIR}/mlx_put_pixel.cc
	${SOURCE_DIR}/mlx_window.cc

	# Utils
	${SOURCE_DIR}/utils/mlx_error.cc
	${SOURCE_DIR}/utils/mlx_list.cc
	${SOURCE_DIR}/utils/mlx_utils.cc
	${SOURCE_DIR}/utils/mlx_compare.cc

	# Textures
	${SOURCE_DIR}/font/mlx_font.cc
	${SOURCE_DIR}/textures/mlx_png.cc
	${SOURCE_DIR}/textures/mlx_texture.cc
	${SOURCE_DIR}/textures/mlx_xpm42.cc

	# Libs
	lib/png/lodepng.cc
	lib/glad/glad.cc

	# Generated shader files
	mlx_vert_shader.cc
	mlx_frag_shader.cc
)

add_library(mlx42 STATIC ${MLX42_SOURCES})

# Force all .cc files to be compiled with the C compiler
foreach(source_file ${MLX42_SOURCES})
    set_source_files_properties(${source_file} PROPERTIES 
        LANGUAGE C
        COMPILE_FLAGS "-x c"
    )
endforeach()

# Also set this globally for .cc extension
set(CMAKE_CC_COMPILE_OBJECT "${CMAKE_C_COMPILE_OBJECT}")

target_include_directories(mlx42 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Dependencies
# -----------------------------------------------------------------------------

find_package(OpenGL REQUIRED)

if(EMSCRIPTEN)
	target_link_libraries(mlx42 "-s USE_GLFW=3" "-s FULL_ES3=1")
else()
	target_link_libraries(mlx42 OpenGL::GL)
	find_package(glfw3)
	if (glfw3_FOUND)
		target_link_libraries(mlx42 ${GLFW3_LIBRARY})
	endif()
	if (NOT glfw3_FOUND AND GLFW_FETCH)
		message(STATUS "Install GLFW to suppress this message")
		message(STATUS "Please wait, fetching GLFW ...")
		include(${CMAKE_DIR}/LinkGLFW.cmake)
		LinkGLFW(mlx42)
	elseif(NOT glfw3_FOUND AND NOT GLFW_FETCH)
		message(FATAL_ERROR "Unable to build: GLFW can't be found nor fetched.")
	endif()
	if(APPLE)
		target_link_libraries(mlx42 "-framework Cocoa" "-framework IOKit")
	endif()
endif()

# Testing
# -----------------------------------------------------------------------------
# Only build tests if we are the main project or explicitly told to, make sure
# tests are not built when mlx42 is included as a subproject, use MLX42_BUILD_TESTS to overwrite this
# use cmake -DBUILD_TESTS=ON/-DMLX42_BUILD_TESTS=ON to build tests

if ((PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME AND BUILD_TESTS) OR MLX42_BUILD_TESTS)
	add_subdirectory(tests)
	enable_testing()
endif()

# Installation
# -----------------------------------------------------------------------------
# Convenience feature to install the library and headers to the system.
# Use cmake -DCMAKE_INSTALL_PREFIX=/usr/local for example to install to /usr/local
# or any other directory that you want to install to.
#
# This only really useful if you are a system administrator and want to install
# the library to the system, if you are a developer you should just use the
# library as a subproject as you probably don't have (nor really should) have any
# ambitions to use this for anything other than your own school projects.

install(
	DIRECTORY ./include/MLX42 DESTINATION ${CMAKE_INSTALL_PREFIX}/include
	FILES_MATCHING PATTERN MLX42.h
)

install(TARGETS mlx42
	EXPORT mlx42Targets
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)