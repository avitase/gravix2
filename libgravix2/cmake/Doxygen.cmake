function(enable_doxygen)
    option(ENABLE_DOXYGEN "Enable doxygen doc builds of source" OFF)
    if (ENABLE_DOXYGEN)
        set(DOXYGEN_GENERATE_HTML YES)
        set(DOXYGEN_CALLER_GRAPH YES)
        set(DOXYGEN_CALL_GRAPH YES)
        set(DOXYGEN_EXTRACT_ALL YES)
        set(DOXYGEN_GENERATE_LATEX YES)
        set(DOXYGEN_USE_MATHJAX YES)
        set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
        find_package(Doxygen REQUIRED dot)

        set(DOC_FILES
            ${PROJECT_SOURCE_DIR}/README.md
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/src
        )

        if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
            doxygen_add_docs(doc ALL ${DOC_FILES})
        else ()
            doxygen_add_docs(doc ${DOC_FILES})
        endif ()
    endif ()
endfunction()