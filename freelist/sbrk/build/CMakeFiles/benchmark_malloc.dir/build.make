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
CMAKE_SOURCE_DIR = /home/killi-pt7716/Desktop/malloc/freelist/sbrk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/killi-pt7716/Desktop/malloc/freelist/sbrk/build

# Include any dependencies generated for this target.
include CMakeFiles/benchmark_malloc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/benchmark_malloc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/benchmark_malloc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/benchmark_malloc.dir/flags.make

CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.o: CMakeFiles/benchmark_malloc.dir/flags.make
CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.o: /home/killi-pt7716/Desktop/malloc/freelist/sbrk/benchmark_malloc.cpp
CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.o: CMakeFiles/benchmark_malloc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/killi-pt7716/Desktop/malloc/freelist/sbrk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.o -MF CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.o.d -o CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.o -c /home/killi-pt7716/Desktop/malloc/freelist/sbrk/benchmark_malloc.cpp

CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/killi-pt7716/Desktop/malloc/freelist/sbrk/benchmark_malloc.cpp > CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.i

CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/killi-pt7716/Desktop/malloc/freelist/sbrk/benchmark_malloc.cpp -o CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.s

# Object files for target benchmark_malloc
benchmark_malloc_OBJECTS = \
"CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.o"

# External object files for target benchmark_malloc
benchmark_malloc_EXTERNAL_OBJECTS =

benchmark_malloc: CMakeFiles/benchmark_malloc.dir/benchmark_malloc.cpp.o
benchmark_malloc: CMakeFiles/benchmark_malloc.dir/build.make
benchmark_malloc: liballocator.a
benchmark_malloc: /usr/lib/x86_64-linux-gnu/libbenchmark.so.1.8.3
benchmark_malloc: CMakeFiles/benchmark_malloc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/killi-pt7716/Desktop/malloc/freelist/sbrk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable benchmark_malloc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/benchmark_malloc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/benchmark_malloc.dir/build: benchmark_malloc
.PHONY : CMakeFiles/benchmark_malloc.dir/build

CMakeFiles/benchmark_malloc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/benchmark_malloc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/benchmark_malloc.dir/clean

CMakeFiles/benchmark_malloc.dir/depend:
	cd /home/killi-pt7716/Desktop/malloc/freelist/sbrk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/killi-pt7716/Desktop/malloc/freelist/sbrk /home/killi-pt7716/Desktop/malloc/freelist/sbrk /home/killi-pt7716/Desktop/malloc/freelist/sbrk/build /home/killi-pt7716/Desktop/malloc/freelist/sbrk/build /home/killi-pt7716/Desktop/malloc/freelist/sbrk/build/CMakeFiles/benchmark_malloc.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/benchmark_malloc.dir/depend
