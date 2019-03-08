cmake_minimum_required(VERSION 2.8)

#project name
project(raytracer_host.exe)

#add readme and todo
set(DATA_FILE ${PROJECT_SOURCE_DIR}/README.md ${PROJECT_SOURCE_DIR}/todo.txt)

###############################
# Custom find modules
###############################
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

##parent dir
set(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE( STATUS "PARENT_DIR: " ${PARENT_DIR})

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#########################################################
# FIND OPENMP (optional)
#########################################################
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

###############################
# Other include paths
###############################
include_directories(src/
                    src/common/
                    src/base/
                    src/glbackend/
                    src/scene/
                    3rdparty/
                    3rdparty/lodepng/)


###############################
# Add source files
###############################
file(GLOB SRC
    src/common/cmdlineparser.h
    src/common/cmdlineparser.cpp
    src/common/logger.h
    src/common/logger.cpp
    src/common/simplebmp.h
    src/common/simplebmp.cpp
    3rdparty/lodepng/*.h
    3rdparty/lodepng/*.cpp
    src/base/*.h
    src/base/*.cpp
    src/glbackend/*.h
    src/glbackend/*.cpp
    src/scene/*.h
    src/scene/*.cpp
    src/*.h
    src/*.cpp
	)

###############################
# Add definitions
###############################
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

###############################
# Linking
###############################
add_executable(raytracer_host.exe ${SRC})
target_link_libraries(raytracer_host.exe ${OPENCL_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
