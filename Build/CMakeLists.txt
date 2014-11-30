#Checking CMake version#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#Setting the project name
project("Arrows")

#set the source files and path
set(SOURCES ../src/main.cpp ../src/Bullet.h ../src/Bullet.cpp ../src/Camera.h ../src/Camera.cpp ../src/Errors.h ../src/Errors.cpp ../src/Game.h ../src/Game.cpp ../src/GLSLProgram.h ../src/GLSLProgram.cpp ../src/GLTexture.h ../src/ImageLoader.h ../src/ImageLoader.cpp ../src/InputManager.h ../src/InputManager.cpp ../src/IOManager.h ../src/IOManager.cpp ../src/picoPNG.h ../src/picoPNG.cpp ../src/ResourceManager.h ../src/ResourceManager.cpp ../src/Sprite.h ../src/Sprite.cpp ../src/SpriteBatch.h ../src/SpriteBatch.cpp ../src/TextureCache.h ../src/TextureCache.cpp ../src/Timing.h ../src/Timing.cpp ../src/Vertex.h ../src/Window.h ../src/Window.cpp)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../Modules)

#Checking all packages are installed
#First OpenGL
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#GLU library
if(NOT OPENGL_GLU_FOUND)
    message(ERROR " GLU not found!")
endif(NOT OPENGL_GLU_FOUND)

#SDL2 library
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(ERROR " SDL2 not found!")
endif(NOT SDL2_FOUND)

#GLU library
find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
	message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)

#Vectormath library
find_package(VECTORMATH REQUIRED)
if(NOT VECTORMATH_FOUND)
	message(ERROR " Vectormath not found!")
endif(NOT VECTORMATH_FOUND)

#Include directories 
include_directories(${SDL2_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS} ${Vectormath_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
#Linker directories
link_directories(${SDL2_LIBRARY_DIRS} ${OpenGL_LIBRARY_DIRS} ${Vectormath_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS})
#Definitions 
add_definitions(${SDL_DEFINITIONS} ${OpenGL_DEFINITIONS} ${Vectormath_DEFINITIONS} ${GLEW_DEFINITIONS})

#Compiler flags depending on the OS 
if (UNIX)
  message(status " Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g")
else()
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif(UNIX)

message(status " ** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

#Define the c++ version used 
add_definitions("-std=c++0x")

#setting and linking the libraries
set(LIBS ${LIBS} ${SDL2_LIBRARY} ${OpenGL_LIBRARY} ${GLEW_LIBRARY} ${Vectormath_LIBRARIES})
link_libraries(${LIBS})

#Create the executable file 
add_executable(Arrows ${SOURCES})

### LINKER ###
target_link_libraries(Arrows GL GLU GLEW SDL2)
