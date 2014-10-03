cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("SimpleGame")

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCES src/Main.cpp)

#INCLUDES
### FIND OpenGL ###
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
  message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
if(NOT OPENGL_GLU_FOUND)
  message(ERROR " GLU not found!")
endif(NOT OPENGL_GLU_FOUND)

### FIND SDL ###
find_package(SDL REQUIRED)
if(NOT SDL_FOUND)
  message(ERROR " SDL not found!")
endif(NOT SDL_FOUND)

### FIND GLEW ###
find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
  message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)

### INCLUDES ###
include_directories(${SDL_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS})

### LINKER ###
link_directories(${SDL_LIBRARY_DIRS} ${OpenGL_LIBRARY_DIRS})

### DEFINITIONS ###
add_definitions(${SDL_DEFINITIONS} ${OpenGL_DEFINITIONS})

### COMPILER FLAGS ###
if (UNIX)
  message(status " Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g -Wall")
else()
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif(UNIX)
  message(status " ** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
  set(LIBS ${LIBS} ${SDL_LIBRARY} ${OpenGL_LIBRARY} ${GLEW_LIBRARY})
link_libraries(${LIBS})

### EXECUTABLE ###
add_executable(SimpleGame ${SOURCES})
