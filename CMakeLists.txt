#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)

# Creates C resources file from files in given directory
function(create_resources dir output_c output_h)
	set(build_dir "${CMAKE_CURRENT_SOURCE_DIR}")
	set(output_c "${build_dir}${output_c}")
	set(output_h "${build_dir}${output_c}")
    # Create empty output file
    file(WRITE ${output_c} "")
	file(WRITE ${output_h} "")
    # Collect input files
    file(GLOB bins ${dir}/*)
    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # Append data to output file
        file(APPEND ${output_c} "const unsigned char ${filename}[] = {${filedata}};\nconst unsigned ${filename}_len = sizeof(${filename});\n")
		file(APPEND ${output_h} "extern \"C\" const unsigned char ${filename}[];\nextern \"C\" const unsigned ${filename}_len;\n")
		
    endforeach()
endfunction()

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(Port-Craft)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Port-Craft_SOURCE_DIR}/assets)

# Set version information in a config.hpp file
set(Port-Craft_VERSION_MAJOR 1)
set(Port-Craft_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.hpp.in"
  "${PROJECT_BINARY_DIR}/config.hpp"
  )
include_directories("${PROJECT_BINARY_DIR}")

# create_resources("gfx" "resource.c" "resources.hpp")

#add_executable(embedfile embedfile.c)

#add_custom_command(
#  OUTPUT texture_png.c
#  COMMAND embedfile
#  ARGS texture_png texture.png
#  DEPENDS texture.png)

# Define sources and executable
set(EXECUTABLE_NAME "Port-Craft")
#file(GLOB Sources "source/*.cpp")
#file(GLOB_RECURSE Sources "source/*/*.cpp")
#file(GLOB_RECURSE Sources "source/*")

file(GLOB_RECURSE Foo_SOURCES "source/*.cpp")
file(GLOB_RECURSE Foo_HEADERS "source/*.hpp")
set (Foo_INCLUDE_DIRS "")
foreach (_headerFile ${Foo_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Foo_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Foo_INCLUDE_DIRS)

include_directories(${Foo_INCLUDE_DIRS})
#add_executable (FooExe ${Foo_SOURCES})

add_executable(${EXECUTABLE_NAME} ${Foo_SOURCES})

set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${Port-Craft_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Port-Craft_VERSION_MINOR}")
include(CPack)