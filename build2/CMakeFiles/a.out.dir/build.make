# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wakatsuki/GoogleDrive/othello

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wakatsuki/GoogleDrive/othello/build2

# Include any dependencies generated for this target.
include CMakeFiles/a.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a.out.dir/flags.make

CMakeFiles/a.out.dir/battle.cpp.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/battle.cpp.o: ../battle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wakatsuki/GoogleDrive/othello/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a.out.dir/battle.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/battle.cpp.o -c /Users/wakatsuki/GoogleDrive/othello/battle.cpp

CMakeFiles/a.out.dir/battle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/battle.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wakatsuki/GoogleDrive/othello/battle.cpp > CMakeFiles/a.out.dir/battle.cpp.i

CMakeFiles/a.out.dir/battle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/battle.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wakatsuki/GoogleDrive/othello/battle.cpp -o CMakeFiles/a.out.dir/battle.cpp.s

CMakeFiles/a.out.dir/battle.cpp.o.requires:

.PHONY : CMakeFiles/a.out.dir/battle.cpp.o.requires

CMakeFiles/a.out.dir/battle.cpp.o.provides: CMakeFiles/a.out.dir/battle.cpp.o.requires
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/battle.cpp.o.provides.build
.PHONY : CMakeFiles/a.out.dir/battle.cpp.o.provides

CMakeFiles/a.out.dir/battle.cpp.o.provides.build: CMakeFiles/a.out.dir/battle.cpp.o


CMakeFiles/a.out.dir/game.cpp.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/game.cpp.o: ../game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wakatsuki/GoogleDrive/othello/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/a.out.dir/game.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/game.cpp.o -c /Users/wakatsuki/GoogleDrive/othello/game.cpp

CMakeFiles/a.out.dir/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/game.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wakatsuki/GoogleDrive/othello/game.cpp > CMakeFiles/a.out.dir/game.cpp.i

CMakeFiles/a.out.dir/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/game.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wakatsuki/GoogleDrive/othello/game.cpp -o CMakeFiles/a.out.dir/game.cpp.s

CMakeFiles/a.out.dir/game.cpp.o.requires:

.PHONY : CMakeFiles/a.out.dir/game.cpp.o.requires

CMakeFiles/a.out.dir/game.cpp.o.provides: CMakeFiles/a.out.dir/game.cpp.o.requires
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/game.cpp.o.provides.build
.PHONY : CMakeFiles/a.out.dir/game.cpp.o.provides

CMakeFiles/a.out.dir/game.cpp.o.provides.build: CMakeFiles/a.out.dir/game.cpp.o


CMakeFiles/a.out.dir/bitboard.cpp.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/bitboard.cpp.o: ../bitboard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wakatsuki/GoogleDrive/othello/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/a.out.dir/bitboard.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/bitboard.cpp.o -c /Users/wakatsuki/GoogleDrive/othello/bitboard.cpp

CMakeFiles/a.out.dir/bitboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/bitboard.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wakatsuki/GoogleDrive/othello/bitboard.cpp > CMakeFiles/a.out.dir/bitboard.cpp.i

CMakeFiles/a.out.dir/bitboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/bitboard.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wakatsuki/GoogleDrive/othello/bitboard.cpp -o CMakeFiles/a.out.dir/bitboard.cpp.s

CMakeFiles/a.out.dir/bitboard.cpp.o.requires:

.PHONY : CMakeFiles/a.out.dir/bitboard.cpp.o.requires

CMakeFiles/a.out.dir/bitboard.cpp.o.provides: CMakeFiles/a.out.dir/bitboard.cpp.o.requires
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/bitboard.cpp.o.provides.build
.PHONY : CMakeFiles/a.out.dir/bitboard.cpp.o.provides

CMakeFiles/a.out.dir/bitboard.cpp.o.provides.build: CMakeFiles/a.out.dir/bitboard.cpp.o


CMakeFiles/a.out.dir/player.cpp.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/player.cpp.o: ../player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wakatsuki/GoogleDrive/othello/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/a.out.dir/player.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/player.cpp.o -c /Users/wakatsuki/GoogleDrive/othello/player.cpp

CMakeFiles/a.out.dir/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/player.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wakatsuki/GoogleDrive/othello/player.cpp > CMakeFiles/a.out.dir/player.cpp.i

CMakeFiles/a.out.dir/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/player.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wakatsuki/GoogleDrive/othello/player.cpp -o CMakeFiles/a.out.dir/player.cpp.s

CMakeFiles/a.out.dir/player.cpp.o.requires:

.PHONY : CMakeFiles/a.out.dir/player.cpp.o.requires

CMakeFiles/a.out.dir/player.cpp.o.provides: CMakeFiles/a.out.dir/player.cpp.o.requires
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/player.cpp.o.provides.build
.PHONY : CMakeFiles/a.out.dir/player.cpp.o.provides

CMakeFiles/a.out.dir/player.cpp.o.provides.build: CMakeFiles/a.out.dir/player.cpp.o


CMakeFiles/a.out.dir/aho.cpp.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/aho.cpp.o: ../aho.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wakatsuki/GoogleDrive/othello/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/a.out.dir/aho.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/aho.cpp.o -c /Users/wakatsuki/GoogleDrive/othello/aho.cpp

CMakeFiles/a.out.dir/aho.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/aho.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wakatsuki/GoogleDrive/othello/aho.cpp > CMakeFiles/a.out.dir/aho.cpp.i

CMakeFiles/a.out.dir/aho.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/aho.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wakatsuki/GoogleDrive/othello/aho.cpp -o CMakeFiles/a.out.dir/aho.cpp.s

CMakeFiles/a.out.dir/aho.cpp.o.requires:

.PHONY : CMakeFiles/a.out.dir/aho.cpp.o.requires

CMakeFiles/a.out.dir/aho.cpp.o.provides: CMakeFiles/a.out.dir/aho.cpp.o.requires
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/aho.cpp.o.provides.build
.PHONY : CMakeFiles/a.out.dir/aho.cpp.o.provides

CMakeFiles/a.out.dir/aho.cpp.o.provides.build: CMakeFiles/a.out.dir/aho.cpp.o


CMakeFiles/a.out.dir/alphabeta.cpp.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/alphabeta.cpp.o: ../alphabeta.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wakatsuki/GoogleDrive/othello/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/a.out.dir/alphabeta.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/alphabeta.cpp.o -c /Users/wakatsuki/GoogleDrive/othello/alphabeta.cpp

CMakeFiles/a.out.dir/alphabeta.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/alphabeta.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wakatsuki/GoogleDrive/othello/alphabeta.cpp > CMakeFiles/a.out.dir/alphabeta.cpp.i

CMakeFiles/a.out.dir/alphabeta.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/alphabeta.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wakatsuki/GoogleDrive/othello/alphabeta.cpp -o CMakeFiles/a.out.dir/alphabeta.cpp.s

CMakeFiles/a.out.dir/alphabeta.cpp.o.requires:

.PHONY : CMakeFiles/a.out.dir/alphabeta.cpp.o.requires

CMakeFiles/a.out.dir/alphabeta.cpp.o.provides: CMakeFiles/a.out.dir/alphabeta.cpp.o.requires
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/alphabeta.cpp.o.provides.build
.PHONY : CMakeFiles/a.out.dir/alphabeta.cpp.o.provides

CMakeFiles/a.out.dir/alphabeta.cpp.o.provides.build: CMakeFiles/a.out.dir/alphabeta.cpp.o


# Object files for target a.out
a_out_OBJECTS = \
"CMakeFiles/a.out.dir/battle.cpp.o" \
"CMakeFiles/a.out.dir/game.cpp.o" \
"CMakeFiles/a.out.dir/bitboard.cpp.o" \
"CMakeFiles/a.out.dir/player.cpp.o" \
"CMakeFiles/a.out.dir/aho.cpp.o" \
"CMakeFiles/a.out.dir/alphabeta.cpp.o"

# External object files for target a.out
a_out_EXTERNAL_OBJECTS =

a.out: CMakeFiles/a.out.dir/battle.cpp.o
a.out: CMakeFiles/a.out.dir/game.cpp.o
a.out: CMakeFiles/a.out.dir/bitboard.cpp.o
a.out: CMakeFiles/a.out.dir/player.cpp.o
a.out: CMakeFiles/a.out.dir/aho.cpp.o
a.out: CMakeFiles/a.out.dir/alphabeta.cpp.o
a.out: CMakeFiles/a.out.dir/build.make
a.out: CMakeFiles/a.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wakatsuki/GoogleDrive/othello/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable a.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a.out.dir/build: a.out

.PHONY : CMakeFiles/a.out.dir/build

CMakeFiles/a.out.dir/requires: CMakeFiles/a.out.dir/battle.cpp.o.requires
CMakeFiles/a.out.dir/requires: CMakeFiles/a.out.dir/game.cpp.o.requires
CMakeFiles/a.out.dir/requires: CMakeFiles/a.out.dir/bitboard.cpp.o.requires
CMakeFiles/a.out.dir/requires: CMakeFiles/a.out.dir/player.cpp.o.requires
CMakeFiles/a.out.dir/requires: CMakeFiles/a.out.dir/aho.cpp.o.requires
CMakeFiles/a.out.dir/requires: CMakeFiles/a.out.dir/alphabeta.cpp.o.requires

.PHONY : CMakeFiles/a.out.dir/requires

CMakeFiles/a.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a.out.dir/clean

CMakeFiles/a.out.dir/depend:
	cd /Users/wakatsuki/GoogleDrive/othello/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wakatsuki/GoogleDrive/othello /Users/wakatsuki/GoogleDrive/othello /Users/wakatsuki/GoogleDrive/othello/build2 /Users/wakatsuki/GoogleDrive/othello/build2 /Users/wakatsuki/GoogleDrive/othello/build2/CMakeFiles/a.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/a.out.dir/depend

