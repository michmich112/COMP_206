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
CMAKE_SOURCE_DIR = /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3

# Include any dependencies generated for this target.
include CMakeFiles/Q3COMP206.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Q3COMP206.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Q3COMP206.dir/flags.make

CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o: CMakeFiles/Q3COMP206.dir/flags.make
CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o: q3_encrypted_chat.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/2016/mcanta5/Code/COMP_206/COMP206_assignment3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o   -c /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3/q3_encrypted_chat.c

CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3/q3_encrypted_chat.c > CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.i

CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3/q3_encrypted_chat.c -o CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.s

CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o.requires:

.PHONY : CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o.requires

CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o.provides: CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o.requires
	$(MAKE) -f CMakeFiles/Q3COMP206.dir/build.make CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o.provides.build
.PHONY : CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o.provides

CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o.provides.build: CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o


# Object files for target Q3COMP206
Q3COMP206_OBJECTS = \
"CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o"

# External object files for target Q3COMP206
Q3COMP206_EXTERNAL_OBJECTS =

Q3COMP206: CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o
Q3COMP206: CMakeFiles/Q3COMP206.dir/build.make
Q3COMP206: libswapLib.so
Q3COMP206: CMakeFiles/Q3COMP206.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/2016/mcanta5/Code/COMP_206/COMP206_assignment3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Q3COMP206"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Q3COMP206.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Q3COMP206.dir/build: Q3COMP206

.PHONY : CMakeFiles/Q3COMP206.dir/build

CMakeFiles/Q3COMP206.dir/requires: CMakeFiles/Q3COMP206.dir/q3_encrypted_chat.c.o.requires

.PHONY : CMakeFiles/Q3COMP206.dir/requires

CMakeFiles/Q3COMP206.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Q3COMP206.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Q3COMP206.dir/clean

CMakeFiles/Q3COMP206.dir/depend:
	cd /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3 /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3 /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3 /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3 /home/2016/mcanta5/Code/COMP_206/COMP206_assignment3/CMakeFiles/Q3COMP206.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Q3COMP206.dir/depend
