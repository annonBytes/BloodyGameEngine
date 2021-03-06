#
# Sub-project CMake file within multi-project solution using AST-Utilities
#

# Minimum required CMAKE version.
cmake_minimum_required(VERSION 3.1)

# Set project name (required by CMake)
project(BagagaDemo)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add executable Target
# (Target name followed by blank-separated C++ source files, no header files!)
add_executable(Demo
        main.cpp 
         ../common/SdlLineRenderer.cpp
        ../common/WindowTitleService.cpp
        ../common/PolylineVisualSystem.cpp
        ../common/AutoRotateSystem.cpp
        ../common/CollisionDetectionSystem.cpp  
        ../common/PlayerMoveSystem.cpp      
        LineRendererTestService.cpp         
        EntityTestService.cpp
        CreateEntityTestService.cpp
        CollisionTestService.cpp
        LinearMovementSystem.cpp
        PlayerTestService.cpp
        ../astu/src/sdl/SdlAudioService.cpp
        ../astu/src/sdl/SdlEventService.cpp
        ../astu/src/sdl/SdlRenderService.cpp
        ../astu/src/sdl/SdlService.cpp
        ../astu/src/sdl/SdlTimeService.cpp
        ../astu/src/sdl/SdlVideoService.cpp
        )

#add include files of commons directory
target_include_directories(Demo PRIVATE ../common)

# Specify required libraries
target_link_libraries(Demo astu)

IF (WIN32)
    target_include_directories(Demo PRIVATE $ENV{SDL2_HOME})
ELSEIF(APPLE)
    target_include_directories(Demo PRIVATE /Library/Frameworks/SDL2.framework/Headers)
    target_link_libraries(Demo /Library/Frameworks/SDL2.framework/Versions/A/SDL2)
ENDIF()
