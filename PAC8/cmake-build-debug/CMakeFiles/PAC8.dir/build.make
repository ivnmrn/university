# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = "/Users/ivan/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/ivan/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ivan/Desktop/C/university/PAC8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ivan/Desktop/C/university/PAC8/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PAC8.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PAC8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PAC8.dir/flags.make

CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.o: CMakeFiles/PAC8.dir/flags.make
CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.o: ../PAC8/source/fairgroundRide.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ivan/Desktop/C/university/PAC8/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.o   -c /Users/ivan/Desktop/C/university/PAC8/PAC8/source/fairgroundRide.c

CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ivan/Desktop/C/university/PAC8/PAC8/source/fairgroundRide.c > CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.i

CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ivan/Desktop/C/university/PAC8/PAC8/source/fairgroundRide.c -o CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.s

CMakeFiles/PAC8.dir/PAC8/source/main.c.o: CMakeFiles/PAC8.dir/flags.make
CMakeFiles/PAC8.dir/PAC8/source/main.c.o: ../PAC8/source/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ivan/Desktop/C/university/PAC8/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/PAC8.dir/PAC8/source/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PAC8.dir/PAC8/source/main.c.o   -c /Users/ivan/Desktop/C/university/PAC8/PAC8/source/main.c

CMakeFiles/PAC8.dir/PAC8/source/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PAC8.dir/PAC8/source/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ivan/Desktop/C/university/PAC8/PAC8/source/main.c > CMakeFiles/PAC8.dir/PAC8/source/main.c.i

CMakeFiles/PAC8.dir/PAC8/source/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PAC8.dir/PAC8/source/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ivan/Desktop/C/university/PAC8/PAC8/source/main.c -o CMakeFiles/PAC8.dir/PAC8/source/main.c.s

# Object files for target PAC8
PAC8_OBJECTS = \
"CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.o" \
"CMakeFiles/PAC8.dir/PAC8/source/main.c.o"

# External object files for target PAC8
PAC8_EXTERNAL_OBJECTS = \
"/Users/ivan/Desktop/C/university/PAC8/PAC8/Debug/source_fairgroundRide.c.o" \
"/Users/ivan/Desktop/C/university/PAC8/PAC8/Debug/source_main.c.o"

PAC8: CMakeFiles/PAC8.dir/PAC8/source/fairgroundRide.c.o
PAC8: CMakeFiles/PAC8.dir/PAC8/source/main.c.o
PAC8: ../PAC8/Debug/source_fairgroundRide.c.o
PAC8: ../PAC8/Debug/source_main.c.o
PAC8: CMakeFiles/PAC8.dir/build.make
PAC8: CMakeFiles/PAC8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ivan/Desktop/C/university/PAC8/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable PAC8"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PAC8.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PAC8.dir/build: PAC8

.PHONY : CMakeFiles/PAC8.dir/build

CMakeFiles/PAC8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PAC8.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PAC8.dir/clean

CMakeFiles/PAC8.dir/depend:
	cd /Users/ivan/Desktop/C/university/PAC8/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ivan/Desktop/C/university/PAC8 /Users/ivan/Desktop/C/university/PAC8 /Users/ivan/Desktop/C/university/PAC8/cmake-build-debug /Users/ivan/Desktop/C/university/PAC8/cmake-build-debug /Users/ivan/Desktop/C/university/PAC8/cmake-build-debug/CMakeFiles/PAC8.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PAC8.dir/depend

