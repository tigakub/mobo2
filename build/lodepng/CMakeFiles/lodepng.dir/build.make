# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tigakub/Documents/OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tigakub/Documents/OpenGL/build

# Include any dependencies generated for this target.
include lodepng/CMakeFiles/lodepng.dir/depend.make

# Include the progress variables for this target.
include lodepng/CMakeFiles/lodepng.dir/progress.make

# Include the compile flags for this target's objects.
include lodepng/CMakeFiles/lodepng.dir/flags.make

lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o: lodepng/CMakeFiles/lodepng.dir/flags.make
lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o: ../lodepng/lodepng.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tigakub/Documents/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lodepng.dir/lodepng.cpp.o -c /home/tigakub/Documents/OpenGL/lodepng/lodepng.cpp

lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lodepng.dir/lodepng.cpp.i"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tigakub/Documents/OpenGL/lodepng/lodepng.cpp > CMakeFiles/lodepng.dir/lodepng.cpp.i

lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lodepng.dir/lodepng.cpp.s"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tigakub/Documents/OpenGL/lodepng/lodepng.cpp -o CMakeFiles/lodepng.dir/lodepng.cpp.s

lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o.requires:

.PHONY : lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o.requires

lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o.provides: lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o.requires
	$(MAKE) -f lodepng/CMakeFiles/lodepng.dir/build.make lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o.provides.build
.PHONY : lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o.provides

lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o.provides.build: lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o


lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o: lodepng/CMakeFiles/lodepng.dir/flags.make
lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o: ../lodepng/lodepng_fuzzer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tigakub/Documents/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o -c /home/tigakub/Documents/OpenGL/lodepng/lodepng_fuzzer.cpp

lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.i"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tigakub/Documents/OpenGL/lodepng/lodepng_fuzzer.cpp > CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.i

lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.s"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tigakub/Documents/OpenGL/lodepng/lodepng_fuzzer.cpp -o CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.s

lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o.requires:

.PHONY : lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o.requires

lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o.provides: lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o.requires
	$(MAKE) -f lodepng/CMakeFiles/lodepng.dir/build.make lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o.provides.build
.PHONY : lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o.provides

lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o.provides.build: lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o


lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o: lodepng/CMakeFiles/lodepng.dir/flags.make
lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o: ../lodepng/lodepng_unittest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tigakub/Documents/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o -c /home/tigakub/Documents/OpenGL/lodepng/lodepng_unittest.cpp

lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lodepng.dir/lodepng_unittest.cpp.i"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tigakub/Documents/OpenGL/lodepng/lodepng_unittest.cpp > CMakeFiles/lodepng.dir/lodepng_unittest.cpp.i

lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lodepng.dir/lodepng_unittest.cpp.s"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tigakub/Documents/OpenGL/lodepng/lodepng_unittest.cpp -o CMakeFiles/lodepng.dir/lodepng_unittest.cpp.s

lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o.requires:

.PHONY : lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o.requires

lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o.provides: lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o.requires
	$(MAKE) -f lodepng/CMakeFiles/lodepng.dir/build.make lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o.provides.build
.PHONY : lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o.provides

lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o.provides.build: lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o


lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o: lodepng/CMakeFiles/lodepng.dir/flags.make
lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o: ../lodepng/lodepng_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tigakub/Documents/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lodepng.dir/lodepng_util.cpp.o -c /home/tigakub/Documents/OpenGL/lodepng/lodepng_util.cpp

lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lodepng.dir/lodepng_util.cpp.i"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tigakub/Documents/OpenGL/lodepng/lodepng_util.cpp > CMakeFiles/lodepng.dir/lodepng_util.cpp.i

lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lodepng.dir/lodepng_util.cpp.s"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tigakub/Documents/OpenGL/lodepng/lodepng_util.cpp -o CMakeFiles/lodepng.dir/lodepng_util.cpp.s

lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o.requires:

.PHONY : lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o.requires

lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o.provides: lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o.requires
	$(MAKE) -f lodepng/CMakeFiles/lodepng.dir/build.make lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o.provides.build
.PHONY : lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o.provides

lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o.provides.build: lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o


lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o: lodepng/CMakeFiles/lodepng.dir/flags.make
lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o: ../lodepng/pngdetail.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tigakub/Documents/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lodepng.dir/pngdetail.cpp.o -c /home/tigakub/Documents/OpenGL/lodepng/pngdetail.cpp

lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lodepng.dir/pngdetail.cpp.i"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tigakub/Documents/OpenGL/lodepng/pngdetail.cpp > CMakeFiles/lodepng.dir/pngdetail.cpp.i

lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lodepng.dir/pngdetail.cpp.s"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tigakub/Documents/OpenGL/lodepng/pngdetail.cpp -o CMakeFiles/lodepng.dir/pngdetail.cpp.s

lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o.requires:

.PHONY : lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o.requires

lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o.provides: lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o.requires
	$(MAKE) -f lodepng/CMakeFiles/lodepng.dir/build.make lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o.provides.build
.PHONY : lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o.provides

lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o.provides.build: lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o


# Object files for target lodepng
lodepng_OBJECTS = \
"CMakeFiles/lodepng.dir/lodepng.cpp.o" \
"CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o" \
"CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o" \
"CMakeFiles/lodepng.dir/lodepng_util.cpp.o" \
"CMakeFiles/lodepng.dir/pngdetail.cpp.o"

# External object files for target lodepng
lodepng_EXTERNAL_OBJECTS =

lodepng/liblodepng.a: lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o
lodepng/liblodepng.a: lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o
lodepng/liblodepng.a: lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o
lodepng/liblodepng.a: lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o
lodepng/liblodepng.a: lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o
lodepng/liblodepng.a: lodepng/CMakeFiles/lodepng.dir/build.make
lodepng/liblodepng.a: lodepng/CMakeFiles/lodepng.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tigakub/Documents/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library liblodepng.a"
	cd /home/tigakub/Documents/OpenGL/build/lodepng && $(CMAKE_COMMAND) -P CMakeFiles/lodepng.dir/cmake_clean_target.cmake
	cd /home/tigakub/Documents/OpenGL/build/lodepng && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lodepng.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lodepng/CMakeFiles/lodepng.dir/build: lodepng/liblodepng.a

.PHONY : lodepng/CMakeFiles/lodepng.dir/build

lodepng/CMakeFiles/lodepng.dir/requires: lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o.requires
lodepng/CMakeFiles/lodepng.dir/requires: lodepng/CMakeFiles/lodepng.dir/lodepng_fuzzer.cpp.o.requires
lodepng/CMakeFiles/lodepng.dir/requires: lodepng/CMakeFiles/lodepng.dir/lodepng_unittest.cpp.o.requires
lodepng/CMakeFiles/lodepng.dir/requires: lodepng/CMakeFiles/lodepng.dir/lodepng_util.cpp.o.requires
lodepng/CMakeFiles/lodepng.dir/requires: lodepng/CMakeFiles/lodepng.dir/pngdetail.cpp.o.requires

.PHONY : lodepng/CMakeFiles/lodepng.dir/requires

lodepng/CMakeFiles/lodepng.dir/clean:
	cd /home/tigakub/Documents/OpenGL/build/lodepng && $(CMAKE_COMMAND) -P CMakeFiles/lodepng.dir/cmake_clean.cmake
.PHONY : lodepng/CMakeFiles/lodepng.dir/clean

lodepng/CMakeFiles/lodepng.dir/depend:
	cd /home/tigakub/Documents/OpenGL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tigakub/Documents/OpenGL /home/tigakub/Documents/OpenGL/lodepng /home/tigakub/Documents/OpenGL/build /home/tigakub/Documents/OpenGL/build/lodepng /home/tigakub/Documents/OpenGL/build/lodepng/CMakeFiles/lodepng.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lodepng/CMakeFiles/lodepng.dir/depend

