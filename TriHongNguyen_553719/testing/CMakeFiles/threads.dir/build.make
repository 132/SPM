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
CMAKE_SOURCE_DIR = /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing

# Include any dependencies generated for this target.
include CMakeFiles/threads.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/threads.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threads.dir/flags.make

CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o: CMakeFiles/threads.dir/flags.make
CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o: ../source/parallelism_thread_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o -c /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/source/parallelism_thread_server.cpp

CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/source/parallelism_thread_server.cpp > CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.i

CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/source/parallelism_thread_server.cpp -o CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.s

CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o.requires:

.PHONY : CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o.requires

CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o.provides: CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o.requires
	$(MAKE) -f CMakeFiles/threads.dir/build.make CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o.provides.build
.PHONY : CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o.provides

CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o.provides.build: CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o


# Object files for target threads
threads_OBJECTS = \
"CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o"

# External object files for target threads
threads_EXTERNAL_OBJECTS =

threads: CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o
threads: CMakeFiles/threads.dir/build.make
threads: libMontecarlo.a
threads: CMakeFiles/threads.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable threads"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threads.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threads.dir/build: threads

.PHONY : CMakeFiles/threads.dir/build

CMakeFiles/threads.dir/requires: CMakeFiles/threads.dir/source/parallelism_thread_server.cpp.o.requires

.PHONY : CMakeFiles/threads.dir/requires

CMakeFiles/threads.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/threads.dir/cmake_clean.cmake
.PHONY : CMakeFiles/threads.dir/clean

CMakeFiles/threads.dir/depend:
	cd /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719 /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719 /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing/CMakeFiles/threads.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/threads.dir/depend
