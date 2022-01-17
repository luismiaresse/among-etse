# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /home/luismi/Apps/clion-2021.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/luismi/Apps/clion-2021.3.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luismi/mega/USC/AlgoEstructDatos/AED-Practicas/AmongETSEfinal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luismi/mega/USC/AlgoEstructDatos/AED-Practicas/AmongETSEfinal

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/luismi/Apps/clion-2021.3.2/bin/cmake/linux/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/home/luismi/Apps/clion-2021.3.2/bin/cmake/linux/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/luismi/mega/USC/AlgoEstructDatos/AED-Practicas/AmongETSEfinal/CMakeFiles /home/luismi/mega/USC/AlgoEstructDatos/AED-Practicas/AmongETSEfinal//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/luismi/mega/USC/AlgoEstructDatos/AED-Practicas/AmongETSEfinal/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named AmongETSEfinal

# Build rule for target.
AmongETSEfinal: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 AmongETSEfinal
.PHONY : AmongETSEfinal

# fast build rule for target.
AmongETSEfinal/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/build
.PHONY : AmongETSEfinal/fast

src/AEMaps.o: src/AEMaps.c.o
.PHONY : src/AEMaps.o

# target to build an object file
src/AEMaps.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/AEMaps.c.o
.PHONY : src/AEMaps.c.o

src/AEMaps.i: src/AEMaps.c.i
.PHONY : src/AEMaps.i

# target to preprocess a source file
src/AEMaps.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/AEMaps.c.i
.PHONY : src/AEMaps.c.i

src/AEMaps.s: src/AEMaps.c.s
.PHONY : src/AEMaps.s

# target to generate assembly for a file
src/AEMaps.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/AEMaps.c.s
.PHONY : src/AEMaps.c.s

src/AEPlay.o: src/AEPlay.c.o
.PHONY : src/AEPlay.o

# target to build an object file
src/AEPlay.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/AEPlay.c.o
.PHONY : src/AEPlay.c.o

src/AEPlay.i: src/AEPlay.c.i
.PHONY : src/AEPlay.i

# target to preprocess a source file
src/AEPlay.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/AEPlay.c.i
.PHONY : src/AEPlay.c.i

src/AEPlay.s: src/AEPlay.c.s
.PHONY : src/AEPlay.s

# target to generate assembly for a file
src/AEPlay.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/AEPlay.c.s
.PHONY : src/AEPlay.c.s

src/AmongETSE.o: src/AmongETSE.c.o
.PHONY : src/AmongETSE.o

# target to build an object file
src/AmongETSE.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/AmongETSE.c.o
.PHONY : src/AmongETSE.c.o

src/AmongETSE.i: src/AmongETSE.c.i
.PHONY : src/AmongETSE.i

# target to preprocess a source file
src/AmongETSE.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/AmongETSE.c.i
.PHONY : src/AmongETSE.c.i

src/AmongETSE.s: src/AmongETSE.c.s
.PHONY : src/AmongETSE.s

# target to generate assembly for a file
src/AmongETSE.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/AmongETSE.c.s
.PHONY : src/AmongETSE.c.s

src/abb.o: src/abb.c.o
.PHONY : src/abb.o

# target to build an object file
src/abb.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/abb.c.o
.PHONY : src/abb.c.o

src/abb.i: src/abb.c.i
.PHONY : src/abb.i

# target to preprocess a source file
src/abb.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/abb.c.i
.PHONY : src/abb.c.i

src/abb.s: src/abb.c.s
.PHONY : src/abb.s

# target to generate assembly for a file
src/abb.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/abb.c.s
.PHONY : src/abb.c.s

src/cola.o: src/cola.c.o
.PHONY : src/cola.o

# target to build an object file
src/cola.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/cola.c.o
.PHONY : src/cola.c.o

src/cola.i: src/cola.c.i
.PHONY : src/cola.i

# target to preprocess a source file
src/cola.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/cola.c.i
.PHONY : src/cola.c.i

src/cola.s: src/cola.c.s
.PHONY : src/cola.s

# target to generate assembly for a file
src/cola.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/cola.c.s
.PHONY : src/cola.c.s

src/common.o: src/common.c.o
.PHONY : src/common.o

# target to build an object file
src/common.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/common.c.o
.PHONY : src/common.c.o

src/common.i: src/common.c.i
.PHONY : src/common.i

# target to preprocess a source file
src/common.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/common.c.i
.PHONY : src/common.c.i

src/common.s: src/common.c.s
.PHONY : src/common.s

# target to generate assembly for a file
src/common.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/common.c.s
.PHONY : src/common.c.s

src/grafo.o: src/grafo.c.o
.PHONY : src/grafo.o

# target to build an object file
src/grafo.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/grafo.c.o
.PHONY : src/grafo.c.o

src/grafo.i: src/grafo.c.i
.PHONY : src/grafo.i

# target to preprocess a source file
src/grafo.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/grafo.c.i
.PHONY : src/grafo.c.i

src/grafo.s: src/grafo.c.s
.PHONY : src/grafo.s

# target to generate assembly for a file
src/grafo.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/grafo.c.s
.PHONY : src/grafo.c.s

src/main.o: src/main.c.o
.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/AmongETSEfinal.dir/build.make CMakeFiles/AmongETSEfinal.dir/src/main.c.s
.PHONY : src/main.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... AmongETSEfinal"
	@echo "... src/AEMaps.o"
	@echo "... src/AEMaps.i"
	@echo "... src/AEMaps.s"
	@echo "... src/AEPlay.o"
	@echo "... src/AEPlay.i"
	@echo "... src/AEPlay.s"
	@echo "... src/AmongETSE.o"
	@echo "... src/AmongETSE.i"
	@echo "... src/AmongETSE.s"
	@echo "... src/abb.o"
	@echo "... src/abb.i"
	@echo "... src/abb.s"
	@echo "... src/cola.o"
	@echo "... src/cola.i"
	@echo "... src/cola.s"
	@echo "... src/common.o"
	@echo "... src/common.i"
	@echo "... src/common.s"
	@echo "... src/grafo.o"
	@echo "... src/grafo.i"
	@echo "... src/grafo.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
