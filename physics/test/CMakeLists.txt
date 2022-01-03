add_executable(planet_tests
        planet_tests.c
        ${PROJECT_SOURCE_DIR}/src/planet.c
)
target_include_directories(planet_tests BEFORE PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(planet_tests PRIVATE project_warnings project_options m)
add_test(planet_tests planet_tests)

add_executable(integrators_tests
    integrators_tests.c
)
target_include_directories(integrators_tests BEFORE PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(integrators_tests PRIVATE project_warnings project_options m)
add_test(integrators_tests integrators_tests)
