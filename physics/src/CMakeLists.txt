add_library(physics SHARED
    helpers.c
    integrators.c
    linalg.c
    missile.c
    planet.c
    pot.c
)
target_include_directories(physics BEFORE PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(physics PRIVATE project_warnings project_options m)
