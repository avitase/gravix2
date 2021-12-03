set(TRAJECTORY_SIZE "5" CACHE STRING "Size of trajectory.")
configure_file(${PROJECT_SOURCE_DIR}/include/config.h.in config.h @ONLY)

add_library(physics SHARED
    missile.c
    world.c
)
target_include_directories(physics BEFORE PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(physics BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(physics PRIVATE project_warnings project_options)
