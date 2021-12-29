add_executable(world_tests
   world_tests.c
   ${PROJECT_SOURCE_DIR}/src/world.c
)
target_include_directories(world_tests BEFORE PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(world_tests PRIVATE project_warnings project_options m)
add_test(world_tests world_tests)

add_executable(integrators_tests
    integrators_tests.c
    ${PROJECT_SOURCE_DIR}/src/integrators.c
    ${PROJECT_SOURCE_DIR}/src/pot.c
    ${PROJECT_SOURCE_DIR}/src/rotation.c
)
target_include_directories(integrators_tests BEFORE PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(integrators_tests PRIVATE project_warnings project_options m)
add_test(integrators_tests integrators_tests)

add_executable(rotation_tests
    rotation_tests.c
    ${PROJECT_SOURCE_DIR}/src/rotation.c
)
target_include_directories(rotation_tests BEFORE PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(rotation_tests PRIVATE project_warnings project_options m)
add_test(rotation_tests rotation_tests)
