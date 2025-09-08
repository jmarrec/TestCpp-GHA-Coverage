cmake_minimum_required(VERSION 3.17.0)
# cmake_policy(SET CMP0048 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Do not enable compiler specific extensions, for eg on GCC use -std=c++1z (=c++17) and not -std=gnu++17
set(CMAKE_CXX_EXTENSIONS OFF)

# Use ccache is available, has to be before "project()"
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  # Support: Unix Makefiles and Ninja only
  message(STATUS "Using CCACHE")
  # RULE_LAUNCH_COMPILE is an internal variable and makes RC compilation fail on windows, hence why we use the C/CXX COMPILER_LAUNCHER instead
  message(STATUS "${CCACHE_PROGRAM} found and enabled")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM} CACHE FILEPATH "CXX compiler cache used")
  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM} CACHE FILEPATH "C compiler cache used")
endif()

project(TestCppCoverage VERSION 0.0.1)

# The PROJECT_SOURCE_DIR here is root of this repo, which we will use instead of using CMAKE_SOURCE_DIR
set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# We will use BINARY_DIR instead of CMAKE_BINARY_DIR
set(PROJECT_BINARY_DIR "${CMAKE_BINARY_DIR}")

#MESSAGE(FATAL_ERROR "CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}, BINARY_DIR=${BINARY_DIR}, PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}, CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}, CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

#if(POLICY CMP0020)
  #cmake_policy(SET CMP0020 NEW)
#endif()
#if(POLICY CMP0022)
  #cmake_policy(SET CMP0022 NEW)
#endif()
#if(POLICY CMP0042)
  #cmake_policy(SET CMP0042 NEW)
#endif()
#if(POLICY CMP0054)
  #cmake_policy(SET CMP0054 NEW)
#endif()
#if(POLICY CMP0077)
  #cmake_policy(SET CMP0077 NEW)
#endif()

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

###############################################################################
#                                  N I N J A                                  #
###############################################################################
# Ninja support: has to be atop for it to take effect before anything else is done
# Add Color Output if Using Ninja
macro(AddCXXFlagIfSupported flag test)
  CHECK_CXX_COMPILER_FLAG(${flag} ${test})
  if(${${test}})
    message("adding ${flag}")
    target_compile_options(project_options INTERFACE "${flag}")
  endif()
endmacro()

if("Ninja" STREQUAL ${CMAKE_GENERATOR})
  # Clang
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    AddCXXFlagIfSupported(-fcolor-diagnostics COMPILER_SUPPORTS_fcolor-diagnostics)
  endif()

  # g++
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # For some reason it doesn't say its supported, but it works...
    # AddCXXFlagIfSupported(-fdiagnostics-color COMPILER_SUPPORTS_fdiagnostics-color)
    message(STATUS "Ninja: Forcing -fdiagnostics-color=always")
    target_compile_options(project_options INTERFACE -fdiagnostics-color=always)
  endif()
endif()

# Xcode/Ninja generators undefined MAKE
if(CMAKE_GENERATOR MATCHES "Make")
  set(MAKE "$(MAKE)")
else()
  set(MAKE make)
endif()

# Enable runtime checking features: TSAN, ASAN, UBSAN
message("CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")
if(CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" ON)
  if(ENABLE_COVERAGE)
    target_compile_options(project_options INTERFACE --coverage -O0 -g)
    target_link_libraries(project_options INTERFACE --coverage)
  endif()
endif()

###############################################################################
#                         C M A K E    C O N T R O L                          #
###############################################################################

# High level project configuration
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/Products")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/Products")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/Products")

set(LIBRARY_SEARCH_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Release" "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug")

###############################################################################
#          C O M P I L E R    A N D    S Y S T E M    O P T I O N S           #
###############################################################################

# Compiler and system specific options
if(UNIX)

  # all warnings
  target_compile_options(project_options INTERFACE -fPIC -fno-strict-aliasing -Winvalid-pch)
  # Treat all warnings as errors, extra errors, and be pedantic
  target_compile_options(project_options INTERFACE -Wall -Wextra -Werror -pedantic-errors -pedantic) # Turn on warnings
  if(APPLE)
     target_compile_options(project_options INTERFACE -Wno-overloaded-virtual -ftemplate-depth=1024)
  endif()

  # Note: CMAKE_CXX_STANDARD set to 20 should already take care of adding -std=c++20 or equivalent
endif()

#######################################################################
#                              C O N A N                              #
#######################################################################

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)


###############################################################################
#                              E X E C U T A B L E                            #
###############################################################################

include_directories(${PROJECT_BINARY_DIR})

add_library(testlib
  src/Person.hpp
  src/Person.cpp
)

target_link_libraries(testlib PRIVATE project_options fmt::fmt)

add_executable(testlib_tests
  test/Person_GTest.cpp
)
target_link_libraries(testlib_tests
  PRIVATE
  testlib
  GTest::gtest_main
)
target_link_libraries(testlib_tests
  PRIVATE
  project_options
)

enable_testing()

include(GoogleTest)
gtest_discover_tests(testlib_tests
  # WORKING_DIRECTORY Testing
)

if (APPLE)
  set(CPACK_IFW_TARGET_DIRECTORY /Applications/TestCpp-GHA-Coverage-${PROJECT_VERSION}/)
elseif(UNIX)

  # For debug
  # set(CPACK_DEBIAN_PACKAGE_DEBUG ON)

  set(CPACK_DEBIAN_PACKAGE_DEPENDS "")

  # These two will set the .deb install path correctly
  set(CPACK_SET_DESTDIR ON)
  set(CPACK_DEBIAN_PACKAGE_NAME "testcpp-gha-coverage-${PROJECT_VERSION}")

  set(CPACK_INSTALL_PREFIX /usr/local/${CPACK_DEBIAN_PACKAGE_NAME})
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Julien")

elseif(WIN32)
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "TestCpp-GHA-Coverage-${PROJECT_VERSION}")
  set(CPACK_IFW_TARGET_DIRECTORY "C:/${CPACK_PACKAGE_INSTALL_DIRECTORY}")
  set(CPACK_BINARY_IFW ON CACHE BOOL "Enable to build IFW packages")
endif()

include(CPack)
include(CPackIFW)

cpack_add_component(Libraries
  DISPLAY_NAME "Libraries"
  DESCRIPTION "Libraries"
)

cpack_add_component(Executable
  DISPLAY_NAME "Test Exe"
  DESCRIPTION "Test Exe"
)

install(TARGETS testlib DESTINATION lib COMPONENT Libraries)
install(TARGETS testlib_tests DESTINATION bin COMPONENT Executable)
