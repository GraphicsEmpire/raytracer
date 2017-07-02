# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /proj/picasso/pourya/repos/raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /proj/picasso/pourya/repos/raytracer

# Include any dependencies generated for this target.
include src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/depend.make

# Include the progress variables for this target.
include src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/progress.make

# Include the compile flags for this target's objects.
include src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/flags.make

src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o: src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/flags.make
src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o: src/3rdparty/yaml-cpp/util/sandbox.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /proj/picasso/pourya/repos/raytracer/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o"
	cd /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util && /opt/rh/devtoolset-2/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sandbox.dir/sandbox.cpp.o -c /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util/sandbox.cpp

src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sandbox.dir/sandbox.cpp.i"
	cd /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util && /opt/rh/devtoolset-2/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util/sandbox.cpp > CMakeFiles/sandbox.dir/sandbox.cpp.i

src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sandbox.dir/sandbox.cpp.s"
	cd /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util && /opt/rh/devtoolset-2/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util/sandbox.cpp -o CMakeFiles/sandbox.dir/sandbox.cpp.s

src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o.requires:
.PHONY : src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o.requires

src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o.provides: src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o.requires
	$(MAKE) -f src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/build.make src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o.provides.build
.PHONY : src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o.provides

src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o.provides.build: src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o

# Object files for target sandbox
sandbox_OBJECTS = \
"CMakeFiles/sandbox.dir/sandbox.cpp.o"

# External object files for target sandbox
sandbox_EXTERNAL_OBJECTS =

src/3rdparty/yaml-cpp/util/sandbox: src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o
src/3rdparty/yaml-cpp/util/sandbox: src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/build.make
src/3rdparty/yaml-cpp/util/sandbox: src/3rdparty/yaml-cpp/libyaml-cpp.a
src/3rdparty/yaml-cpp/util/sandbox: src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sandbox"
	cd /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sandbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/build: src/3rdparty/yaml-cpp/util/sandbox
.PHONY : src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/build

src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/requires: src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/sandbox.cpp.o.requires
.PHONY : src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/requires

src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/clean:
	cd /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util && $(CMAKE_COMMAND) -P CMakeFiles/sandbox.dir/cmake_clean.cmake
.PHONY : src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/clean

src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/depend:
	cd /proj/picasso/pourya/repos/raytracer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /proj/picasso/pourya/repos/raytracer /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util /proj/picasso/pourya/repos/raytracer /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util /proj/picasso/pourya/repos/raytracer/src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/3rdparty/yaml-cpp/util/CMakeFiles/sandbox.dir/depend
