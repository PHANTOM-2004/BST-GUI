
set(TESTS_SOURCES bst_test.cc)

qt_add_executable(BST_TEST
        MANUAL_FINALIZATION
        ${TESTS_SOURCES}
    )

# enable address sanitizer
target_compile_options(BST_TEST PRIVATE -fsanitize=address)
target_link_options(BST_TEST PRIVATE -fsanitize=address)

target_link_libraries(BST_TEST PRIVATE Qt6::Widgets)


qt_finalize_executable(BST_TEST)
