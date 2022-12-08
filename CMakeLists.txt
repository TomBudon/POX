cmake_minimum_required(VERSION 3.10)

# set the project name
project(POO)

# enable modern C++
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS -fvisibility=hidden)


# add the executable
add_executable(exec.exe main.cpp GenericExample.cpp HypreAPI.cpp PETScAPI.cpp SolverFabric.cpp LocalLinearAlgebra.cpp)
#
# add_subdirectory(mylib_dir)
#
# target_link_libraries(Main.exe PUBLIC mylib)
# target_include_directories(Main.exe PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           "${PROJECT_SOURCE_DIR}/mylib_dir"
# )
#
#
# target_compile_options( Main.exe PRIVATE -fvisibility=hidden)

##################### TEST ###################




enable_testing()
find_package(GTest REQUIRED)

add_executable(Test.exe test.cpp GenericExample.cpp HypreAPI.cpp PETScAPI.cpp SolverFabric.cpp LocalLinearAlgebra.cpp)

target_link_libraries(Test.exe GTest::GTest GTest::Main )
#
# target_include_directories(Test.exe PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           "${PROJECT_SOURCE_DIR}/mylib_dir"
#                           )
#

gtest_discover_tests(Test.exe)
add_test( Test Main.exe)


