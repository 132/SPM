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
include CMakeFiles/seq.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/seq.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/seq.dir/flags.make

CMakeFiles/seq.dir/source/sequantialization.cpp.o: CMakeFiles/seq.dir/flags.make
CMakeFiles/seq.dir/source/sequantialization.cpp.o: ../source/sequantialization.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/seq.dir/source/sequantialization.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/seq.dir/source/sequantialization.cpp.o -c /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/source/sequantialization.cpp

CMakeFiles/seq.dir/source/sequantialization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/seq.dir/source/sequantialization.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/source/sequantialization.cpp > CMakeFiles/seq.dir/source/sequantialization.cpp.i

CMakeFiles/seq.dir/source/sequantialization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/seq.dir/source/sequantialization.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/source/sequantialization.cpp -o CMakeFiles/seq.dir/source/sequantialization.cpp.s

CMakeFiles/seq.dir/source/sequantialization.cpp.o.requires:

.PHONY : CMakeFiles/seq.dir/source/sequantialization.cpp.o.requires

CMakeFiles/seq.dir/source/sequantialization.cpp.o.provides: CMakeFiles/seq.dir/source/sequantialization.cpp.o.requires
	$(MAKE) -f CMakeFiles/seq.dir/build.make CMakeFiles/seq.dir/source/sequantialization.cpp.o.provides.build
.PHONY : CMakeFiles/seq.dir/source/sequantialization.cpp.o.provides

CMakeFiles/seq.dir/source/sequantialization.cpp.o.provides.build: CMakeFiles/seq.dir/source/sequantialization.cpp.o


# Object files for target seq
seq_OBJECTS = \
"CMakeFiles/seq.dir/source/sequantialization.cpp.o"

# External object files for target seq
seq_EXTERNAL_OBJECTS =

seq: CMakeFiles/seq.dir/source/sequantialization.cpp.o
seq: CMakeFiles/seq.dir/build.make
seq: libMontecarlo.a
seq: CMakeFiles/seq.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable seq"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/seq.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/seq.dir/build: seq

.PHONY : CMakeFiles/seq.dir/build

CMakeFiles/seq.dir/requires: CMakeFiles/seq.dir/source/sequantialization.cpp.o.requires

.PHONY : CMakeFiles/seq.dir/requires

CMakeFiles/seq.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/seq.dir/cmake_clean.cmake
.PHONY : CMakeFiles/seq.dir/clean

CMakeFiles/seq.dir/depend:
	cd /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719 /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719 /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing /home/bialan132/Public/Studying/SPM/SPM/TriHongNguyen_553719/testing/CMakeFiles/seq.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/seq.dir/depend

