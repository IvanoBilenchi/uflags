#################
# Configuration #
#################

# CMake

cmake_minimum_required(VERSION 3.13)

# Project

project(uFlags
        VERSION 0.1.0
        DESCRIPTION "Collection of C primitives to safely manipulate bitmasks."
        HOMEPAGE_URL "https://github.com/IvanoBilenchi/uflags"
        LANGUAGES C)

###########
# Targets #
###########

# Interface library

add_library(uflags INTERFACE)
target_sources(uflags INTERFACE "include/uflags.h")
target_include_directories(uflags INTERFACE "include")

# Subprojects

add_subdirectory("test")
add_subdirectory("docs")
