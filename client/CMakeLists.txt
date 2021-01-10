#
# Sub-project CMake file within multi-project solution using AST-Utilities
#

# Minimum required CMAKE version.
cmake_minimum_required(VERSION 3.1)

# Set project name (required by CMake)
project(BagagaClient)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)


# Add executable Target
# (Target name followed by blank-separated C++ source files, no header files!)
add_executable(Client
        main.cpp 
        ../common/SdlLineRenderer.cpp
        )

#add include files of commons directory
target_include_directories(Client PRIVATE ../common)

# Specify required libraries
target_link_libraries(Client astu)

IF (WIN32)
    target_include_directories(Client PRIVATE $ENV{SDL2_HOME})
ELSEIF(APPLE)
    target_include_directories(Client PRIVATE /Library/Frameworks/SDL2.framework/Headers)
    target_link_libraries(Client /Library/Frameworks/SDL2.framework/Versions/A/SDL2)
ENDIF()
