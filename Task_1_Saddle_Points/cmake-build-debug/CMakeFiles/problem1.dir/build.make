# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\JetBrains\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\JetBrains\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/problem1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/problem1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/problem1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/problem1.dir/flags.make

CMakeFiles/problem1.dir/main.c.obj: CMakeFiles/problem1.dir/flags.make
CMakeFiles/problem1.dir/main.c.obj: ../main.c
CMakeFiles/problem1.dir/main.c.obj: CMakeFiles/problem1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/problem1.dir/main.c.obj"
	"D:\JetBrains\CLion 2021.3.3\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/problem1.dir/main.c.obj -MF CMakeFiles\problem1.dir\main.c.obj.d -o CMakeFiles\problem1.dir\main.c.obj -c D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points\main.c

CMakeFiles/problem1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/problem1.dir/main.c.i"
	"D:\JetBrains\CLion 2021.3.3\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points\main.c > CMakeFiles\problem1.dir\main.c.i

CMakeFiles/problem1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/problem1.dir/main.c.s"
	"D:\JetBrains\CLion 2021.3.3\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points\main.c -o CMakeFiles\problem1.dir\main.c.s

# Object files for target problem1
problem1_OBJECTS = \
"CMakeFiles/problem1.dir/main.c.obj"

# External object files for target problem1
problem1_EXTERNAL_OBJECTS =

problem1.exe: CMakeFiles/problem1.dir/main.c.obj
problem1.exe: CMakeFiles/problem1.dir/build.make
problem1.exe: CMakeFiles/problem1.dir/linklibs.rsp
problem1.exe: CMakeFiles/problem1.dir/objects1.rsp
problem1.exe: CMakeFiles/problem1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable problem1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\problem1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/problem1.dir/build: problem1.exe
.PHONY : CMakeFiles/problem1.dir/build

CMakeFiles/problem1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\problem1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/problem1.dir/clean

CMakeFiles/problem1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points\cmake-build-debug D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points\cmake-build-debug D:\CLionProjects\C\C_tasks\Task_1_Saddle_Points\cmake-build-debug\CMakeFiles\problem1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/problem1.dir/depend
