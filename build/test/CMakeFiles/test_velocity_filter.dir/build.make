# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/phil/Arduino/libraries/robopi_drivers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/phil/Arduino/libraries/robopi_drivers/build

# Include any dependencies generated for this target.
include test/CMakeFiles/test_velocity_filter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/test_velocity_filter.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_velocity_filter.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_velocity_filter.dir/flags.make

test/CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.o: test/CMakeFiles/test_velocity_filter.dir/flags.make
test/CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.o: ../test/test_velocity_filter.cpp
test/CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.o: test/CMakeFiles/test_velocity_filter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/phil/Arduino/libraries/robopi_drivers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.o"
	cd /home/phil/Arduino/libraries/robopi_drivers/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.o -MF CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.o.d -o CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.o -c /home/phil/Arduino/libraries/robopi_drivers/test/test_velocity_filter.cpp

test/CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.i"
	cd /home/phil/Arduino/libraries/robopi_drivers/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/phil/Arduino/libraries/robopi_drivers/test/test_velocity_filter.cpp > CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.i

test/CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.s"
	cd /home/phil/Arduino/libraries/robopi_drivers/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/phil/Arduino/libraries/robopi_drivers/test/test_velocity_filter.cpp -o CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.s

test/CMakeFiles/test_velocity_filter.dir/csv.cpp.o: test/CMakeFiles/test_velocity_filter.dir/flags.make
test/CMakeFiles/test_velocity_filter.dir/csv.cpp.o: ../test/csv.cpp
test/CMakeFiles/test_velocity_filter.dir/csv.cpp.o: test/CMakeFiles/test_velocity_filter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/phil/Arduino/libraries/robopi_drivers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/test_velocity_filter.dir/csv.cpp.o"
	cd /home/phil/Arduino/libraries/robopi_drivers/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/test_velocity_filter.dir/csv.cpp.o -MF CMakeFiles/test_velocity_filter.dir/csv.cpp.o.d -o CMakeFiles/test_velocity_filter.dir/csv.cpp.o -c /home/phil/Arduino/libraries/robopi_drivers/test/csv.cpp

test/CMakeFiles/test_velocity_filter.dir/csv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_velocity_filter.dir/csv.cpp.i"
	cd /home/phil/Arduino/libraries/robopi_drivers/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/phil/Arduino/libraries/robopi_drivers/test/csv.cpp > CMakeFiles/test_velocity_filter.dir/csv.cpp.i

test/CMakeFiles/test_velocity_filter.dir/csv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_velocity_filter.dir/csv.cpp.s"
	cd /home/phil/Arduino/libraries/robopi_drivers/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/phil/Arduino/libraries/robopi_drivers/test/csv.cpp -o CMakeFiles/test_velocity_filter.dir/csv.cpp.s

# Object files for target test_velocity_filter
test_velocity_filter_OBJECTS = \
"CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.o" \
"CMakeFiles/test_velocity_filter.dir/csv.cpp.o"

# External object files for target test_velocity_filter
test_velocity_filter_EXTERNAL_OBJECTS =

test/test_velocity_filter: test/CMakeFiles/test_velocity_filter.dir/test_velocity_filter.cpp.o
test/test_velocity_filter: test/CMakeFiles/test_velocity_filter.dir/csv.cpp.o
test/test_velocity_filter: test/CMakeFiles/test_velocity_filter.dir/build.make
test/test_velocity_filter: libbot_low_level.a
test/test_velocity_filter: test/CMakeFiles/test_velocity_filter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/phil/Arduino/libraries/robopi_drivers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_velocity_filter"
	cd /home/phil/Arduino/libraries/robopi_drivers/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_velocity_filter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_velocity_filter.dir/build: test/test_velocity_filter
.PHONY : test/CMakeFiles/test_velocity_filter.dir/build

test/CMakeFiles/test_velocity_filter.dir/clean:
	cd /home/phil/Arduino/libraries/robopi_drivers/build/test && $(CMAKE_COMMAND) -P CMakeFiles/test_velocity_filter.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_velocity_filter.dir/clean

test/CMakeFiles/test_velocity_filter.dir/depend:
	cd /home/phil/Arduino/libraries/robopi_drivers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/phil/Arduino/libraries/robopi_drivers /home/phil/Arduino/libraries/robopi_drivers/test /home/phil/Arduino/libraries/robopi_drivers/build /home/phil/Arduino/libraries/robopi_drivers/build/test /home/phil/Arduino/libraries/robopi_drivers/build/test/CMakeFiles/test_velocity_filter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_velocity_filter.dir/depend
