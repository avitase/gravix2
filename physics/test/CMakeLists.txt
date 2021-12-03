add_executable(tests world_tests.c ${PROJECT_SOURCE_DIR}/src/world.c)
target_include_directories(tests BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE project_warnings project_options)
add_test(tests tests)