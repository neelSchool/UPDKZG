# Add subdirectories for each third-party library
add_subdirectory(third_party/blst)
add_subdirectory(third_party/libff)
add_subdirectory(third_party/googletest)
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
