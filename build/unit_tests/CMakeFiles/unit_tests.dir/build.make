# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build

# Include any dependencies generated for this target.
include unit_tests/CMakeFiles/unit_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unit_tests/CMakeFiles/unit_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include unit_tests/CMakeFiles/unit_tests.dir/progress.make

# Include the compile flags for this target's objects.
include unit_tests/CMakeFiles/unit_tests.dir/flags.make

unit_tests/CMakeFiles/unit_tests.dir/src/unit_tests.cpp.o: unit_tests/CMakeFiles/unit_tests.dir/flags.make
unit_tests/CMakeFiles/unit_tests.dir/src/unit_tests.cpp.o: /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/unit_tests/src/unit_tests.cpp
unit_tests/CMakeFiles/unit_tests.dir/src/unit_tests.cpp.o: unit_tests/CMakeFiles/unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unit_tests/CMakeFiles/unit_tests.dir/src/unit_tests.cpp.o"
	cd /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unit_tests/CMakeFiles/unit_tests.dir/src/unit_tests.cpp.o -MF CMakeFiles/unit_tests.dir/src/unit_tests.cpp.o.d -o CMakeFiles/unit_tests.dir/src/unit_tests.cpp.o -c /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/unit_tests/src/unit_tests.cpp

unit_tests/CMakeFiles/unit_tests.dir/src/unit_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/src/unit_tests.cpp.i"
	cd /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/unit_tests/src/unit_tests.cpp > CMakeFiles/unit_tests.dir/src/unit_tests.cpp.i

unit_tests/CMakeFiles/unit_tests.dir/src/unit_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/src/unit_tests.cpp.s"
	cd /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/unit_tests/src/unit_tests.cpp -o CMakeFiles/unit_tests.dir/src/unit_tests.cpp.s

unit_tests/CMakeFiles/unit_tests.dir/main.cpp.o: unit_tests/CMakeFiles/unit_tests.dir/flags.make
unit_tests/CMakeFiles/unit_tests.dir/main.cpp.o: /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/unit_tests/main.cpp
unit_tests/CMakeFiles/unit_tests.dir/main.cpp.o: unit_tests/CMakeFiles/unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object unit_tests/CMakeFiles/unit_tests.dir/main.cpp.o"
	cd /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unit_tests/CMakeFiles/unit_tests.dir/main.cpp.o -MF CMakeFiles/unit_tests.dir/main.cpp.o.d -o CMakeFiles/unit_tests.dir/main.cpp.o -c /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/unit_tests/main.cpp

unit_tests/CMakeFiles/unit_tests.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/main.cpp.i"
	cd /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/unit_tests/main.cpp > CMakeFiles/unit_tests.dir/main.cpp.i

unit_tests/CMakeFiles/unit_tests.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/main.cpp.s"
	cd /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/unit_tests/main.cpp -o CMakeFiles/unit_tests.dir/main.cpp.s

# Object files for target unit_tests
unit_tests_OBJECTS = \
"CMakeFiles/unit_tests.dir/src/unit_tests.cpp.o" \
"CMakeFiles/unit_tests.dir/main.cpp.o"

# External object files for target unit_tests
unit_tests_EXTERNAL_OBJECTS =

unit_tests/unit_tests: unit_tests/CMakeFiles/unit_tests.dir/src/unit_tests.cpp.o
unit_tests/unit_tests: unit_tests/CMakeFiles/unit_tests.dir/main.cpp.o
unit_tests/unit_tests: unit_tests/CMakeFiles/unit_tests.dir/build.make
unit_tests/unit_tests: /Users/bulatmotygullin/.conan2/p/b/gtestf3dfc7ba291a7/p/lib/libgtest_main.a
unit_tests/unit_tests: /Users/bulatmotygullin/.conan2/p/b/gtestf3dfc7ba291a7/p/lib/libgtest.a
unit_tests/unit_tests: unit_tests/CMakeFiles/unit_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable unit_tests"
	cd /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unit_tests/CMakeFiles/unit_tests.dir/build: unit_tests/unit_tests
.PHONY : unit_tests/CMakeFiles/unit_tests.dir/build

unit_tests/CMakeFiles/unit_tests.dir/clean:
	cd /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests && $(CMAKE_COMMAND) -P CMakeFiles/unit_tests.dir/cmake_clean.cmake
.PHONY : unit_tests/CMakeFiles/unit_tests.dir/clean

unit_tests/CMakeFiles/unit_tests.dir/depend:
	cd /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/unit_tests /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests /Users/bulatmotygullin/Documents/CPP_Industrial/Matrix/build/unit_tests/CMakeFiles/unit_tests.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : unit_tests/CMakeFiles/unit_tests.dir/depend

