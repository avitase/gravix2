add_library(physics SHARED
    integrators.c
    missile.c
    pot.c
    rotation.c
    world.c
)
target_include_directories(physics BEFORE PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(physics PRIVATE project_warnings project_options m)
