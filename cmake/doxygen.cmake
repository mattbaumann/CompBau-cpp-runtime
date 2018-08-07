
function(build_doxygen)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/doxygen.config)
        set(DOXYGEN_OUT ${PROJECT_SOURCE_DIR}/doxygen/doxygen.tmp)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        add_custom_target(doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM
                )
    else (DOXYGEN_FOUND)
        message("Install doxygen for project documentation")
    endif (DOXYGEN_FOUND)
endfunction()