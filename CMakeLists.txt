cmake_minimum_required(VERSION 3.16)
project(upkzg)

add_subdirectory(third_party/googletest)
# find and link blst / libff: you will add find_package or add_subdirectory for them
include_directories(include)
add_executable(test_poly tests/unit/test_poly.cpp src/poly.cpp ...)
target_link_libraries(test_poly gtest_main blst libff)
add_test(NAME poly_test COMMAND test_poly)
