file(GLOB_RECURSE QBST_SOURCES
${CMAKE_SOURCE_DIR}/src/qbst/*.cc
${CMAKE_SOURCE_DIR}/include/qbst/*.hpp
)

set(TESTS_SOURCES
bst_test.cc bst_test.hpp
${QBST_SOURCES}
)
message("Test Source files are listed below")
foreach(f IN LISTS TESTS_SOURCES)
  message("${f}")
endforeach()
message("Test Source files end")

qt_add_executable(BST_TEST
        MANUAL_FINALIZATION
        ${TESTS_SOURCES}
    )

# enable address sanitizer
target_compile_options(BST_TEST PRIVATE -fsanitize=address)
target_link_options(BST_TEST PRIVATE -fsanitize=address)

target_link_libraries(BST_TEST PRIVATE Qt6::Widgets)


qt_finalize_executable(BST_TEST)
