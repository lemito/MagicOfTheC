cmake_minimum_required(VERSION 3.27)
project(MagicOfTheC C)

set(CMAKE_C_STANDARD 11)

# Create lib as lib
add_library(MagicOfTheC_vector STATIC src/vector/vector_lib.c)
add_library(MagicOfTheC_stack_arr STATIC src/stack/stack_arr_lib.c)
add_library(MagicOfTheC_tree_lib STATIC src/tree/tree_lib.c)
# Create executable point
add_executable(MagicOfTheC_vector_bin src/vector/vector.c)
add_executable(MagicOfTheC_tree_bin src/tree/tree.c)
# Link executable and library
target_link_libraries(MagicOfTheC_vector_bin MagicOfTheC_vector)
target_link_libraries(MagicOfTheC_tree_bin MagicOfTheC_tree_lib)