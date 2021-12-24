cmake_minimum_required(VERSION 3.19)

project(physics C)

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE c_std_11)

add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Linker.cmake)
configure_linker(project_options)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/Doxygen.cmake)
enable_doxygen()

option(ENABLE_TESTING "Enable Test Builds" OFF)
if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif ()

add_subdirectory(src)

set(N_POT "5" CACHE STRING "Approximation order of potential")

set(TRAJECTORY_SIZE "5" CACHE STRING "Size of trajectory")

set(COMPOSITION_SCHEME "p8s15" CACHE STRING "Composition method of integrator")
set(COMPOSITION_SCHEME_VALUES "p2s1" "p4s5" "p6s9" "p8s15")
set_property(CACHE COMPOSITION_SCHEME PROPERTY STRINGS ${COMPOSITION_SCHEME_VALUES})
list(FIND COMPOSITION_SCHEME_VALUES ${COMPOSITION_SCHEME} COMPOSITION_SCHEME_INDEX)

if (${COMPOSITION_SCHEME_INDEX} EQUAL -1)
    message(FATAL_ERROR "Unkown composition method '${COMPOSITION_SCHEME}'; supported entries are ${COMPOSITION_SCHEME_VALUES}")
else ()
    message(STATUS "Using composition method: ${COMPOSITION_SCHEME}")
endif ()


configure_file(${PROJECT_SOURCE_DIR}/include/config.h.in src/config.h @ONLY)
configure_file(${PROJECT_SOURCE_DIR}/include/config.h.in test/config.h @ONLY)

