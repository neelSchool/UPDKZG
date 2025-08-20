# Add subdirectories for each third-party library
add_subdirectory(third_party/blst)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)       # global CTest off
set(ENABLE_TESTS OFF CACHE BOOL "" FORCE)        # libsnark/libff specific
set(BUILD_LIBFF_TESTS OFF CACHE BOOL "" FORCE)   # libff flag
set(BUILD_LIBSNARK_TESTS OFF CACHE BOOL "" FORCE)# libsnark flag
add_subdirectory(third_party/libff)
add_subdirectory(third_party/libsnark)
add_subdirectory(third_party/gmp)

# Include directories for the third-party libraries
include_directories(
    third_party/blst/include
    third_party/libff/include
    third_party/googletest/googletest/include
    third_party/libsnark
    third_party/gmp/include
)

# Link the libraries to your target
target_link_libraries(UpdatableZK
    blst
    libff
    gtest_main
    libsnark
    gmp
)
# Bring in only our gtest
add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)

# Your tests
enable_testing()
file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(kupcom_tests ${TEST_SOURCES})
target_link_libraries(kupcom_tests PRIVATE kupcom gtest gtest_main)
add_test(NAME kupcom_tests COMMAND kupcom_tests)