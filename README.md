

Thanks to load PNG for the code to help display PNG files.

A big thanks to Making Games with Ben, on youtube for the amazing tutorials which helped me get started with this project!

Grab the Download from my repository: https://github.com/CrazyRagdoll/Arrows/archive/master.zip

Requires Ubuntu 12.04/14.04

Required libraries & extensions (Ubuntu terminal commands to install libaries): 

Cmake: sudo apt-get install cmake /n
GLEW: sudo apt-get install libglew-dev
SDL2.0: sudo apt-get install libsdl2-dev
SOIL: sudo apt-get install libsoil-dev 
OpenGL & GLM: Should be pre-installed on the Ubuntu OS

To Run:

Open Ubuntu terminal and navigate to ../Arrows/Build/

Enter “cmake CMakeLists.txt” to build project (Cmake might shout at you because there are different source directories. This is because the project has already been built! Delete all files in that folder except for CMakeLists.txt)

Enter “make” to compile project

Enter “/Arrows” to run the project
