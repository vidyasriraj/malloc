# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/killi-pt7716/Desktop/malloc/buddy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/killi-pt7716/Desktop/malloc/buddy/build

# Include any dependencies generated for this target.
include CMakeFiles/large.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/large.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/large.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/large.dir/flags.make

CMakeFiles/large.dir/large.cpp.o: CMakeFiles/large.dir/flags.make
CMakeFiles/large.dir/large.cpp.o: /home/killi-pt7716/Desktop/malloc/buddy/large.cpp
CMakeFiles/large.dir/large.cpp.o: CMakeFiles/large.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/killi-pt7716/Desktop/malloc/buddy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/large.dir/large.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/large.dir/large.cpp.o -MF CMakeFiles/large.dir/large.cpp.o.d -o CMakeFiles/large.dir/large.cpp.o -c /home/killi-pt7716/Desktop/malloc/buddy/large.cpp

CMakeFiles/large.dir/large.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/large.dir/large.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/killi-pt7716/Desktop/malloc/buddy/large.cpp > CMakeFiles/large.dir/large.cpp.i

CMakeFiles/large.dir/large.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/large.dir/large.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/killi-pt7716/Desktop/malloc/buddy/large.cpp -o CMakeFiles/large.dir/large.cpp.s

# Object files for target large
large_OBJECTS = \
"CMakeFiles/large.dir/large.cpp.o"

# External object files for target large
large_EXTERNAL_OBJECTS =

large: CMakeFiles/large.dir/large.cpp.o
large: CMakeFiles/large.dir/build.make
large: liballocator.a
large: CMakeFiles/large.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/killi-pt7716/Desktop/malloc/buddy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable large"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/large.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/large.dir/build: large
.PHONY : CMakeFiles/large.dir/build

CMakeFiles/large.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/large.dir/cmake_clean.cmake
.PHONY : CMakeFiles/large.dir/clean

CMakeFiles/large.dir/depend:
	cd /home/killi-pt7716/Desktop/malloc/buddy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/killi-pt7716/Desktop/malloc/buddy /home/killi-pt7716/Desktop/malloc/buddy /home/killi-pt7716/Desktop/malloc/buddy/build /home/killi-pt7716/Desktop/malloc/buddy/build /home/killi-pt7716/Desktop/malloc/buddy/build/CMakeFiles/large.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/large.dir/depend

