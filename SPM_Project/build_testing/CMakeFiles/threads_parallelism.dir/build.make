# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/bialan132/Public/Studying/SPM/SPM/SPM_Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bialan132/Public/Studying/SPM/SPM/SPM_Project/build_testing

# Include any dependencies generated for this target.
include CMakeFiles/threads_parallelism.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/threads_parallelism.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threads_parallelism.dir/flags.make

CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o: CMakeFiles/threads_parallelism.dir/flags.make
CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o: ../implement/parallelism_thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bialan132/Public/Studying/SPM/SPM/SPM_Project/build_testing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o -c /home/bialan132/Public/Studying/SPM/SPM/SPM_Project/implement/parallelism_thread.cpp

CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bialan132/Public/Studying/SPM/SPM/SPM_Project/implement/parallelism_thread.cpp > CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.i

CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bialan132/Public/Studying/SPM/SPM/SPM_Project/implement/parallelism_thread.cpp -o CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.s

CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o.requires:

.PHONY : CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o.requires

CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o.provides: CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/threads_parallelism.dir/build.make CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o.provides.build
.PHONY : CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o.provides

CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o.provides.build: CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o


# Object files for target threads_parallelism
threads_parallelism_OBJECTS = \
"CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o"

# External object files for target threads_parallelism
threads_parallelism_EXTERNAL_OBJECTS =

threads_parallelism: CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o
threads_parallelism: CMakeFiles/threads_parallelism.dir/build.make
threads_parallelism: libMontecarlo.a
threads_parallelism: CMakeFiles/threads_parallelism.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bialan132/Public/Studying/SPM/SPM/SPM_Project/build_testing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable threads_parallelism"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threads_parallelism.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threads_parallelism.dir/build: threads_parallelism

.PHONY : CMakeFiles/threads_parallelism.dir/build

CMakeFiles/threads_parallelism.dir/requires: CMakeFiles/threads_parallelism.dir/implement/parallelism_thread.cpp.o.requires

.PHONY : CMakeFiles/threads_parallelism.dir/requires

CMakeFiles/threads_parallelism.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/threads_parallelism.dir/cmake_clean.cmake
.PHONY : CMakeFiles/threads_parallelism.dir/clean

CMakeFiles/threads_parallelism.dir/depend:
	cd /home/bialan132/Public/Studying/SPM/SPM/SPM_Project/build_testing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bialan132/Public/Studying/SPM/SPM/SPM_Project /home/bialan132/Public/Studying/SPM/SPM/SPM_Project /home/bialan132/Public/Studying/SPM/SPM/SPM_Project/build_testing /home/bialan132/Public/Studying/SPM/SPM/SPM_Project/build_testing /home/bialan132/Public/Studying/SPM/SPM/SPM_Project/build_testing/CMakeFiles/threads_parallelism.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/threads_parallelism.dir/depend
