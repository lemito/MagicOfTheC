cmake_minimum_required(VERSION 3.27)
project(MagicOfTheC C)

set(CMAKE_C_STANDARD 11)

# Create lib as lib
add_library(MagicOfTheC_vector STATIC src/vector/vector_lib.c)
add_library(MagicOfTheC_exp_tree_libs STATIC src/lab24/stack.c src/lab24/stack.h src/lab24/symbol.h src/lab24/token.h src/lab24/tree.h)
add_library(MagicOfTheC_stack_arr STATIC src/stack/stack_arr_lib.c
        src/linear_list/main.c)
add_library(MagicOfTheC_tree_lib STATIC src/tree/tree_lib.c)
add_library(MagicOfTheC_queue_dyn_lib STATIC src/queue/queue_dyn_lib.c)
add_library(MagicOfTheC_queue_static_lib STATIC src/queue/queue_static_lib.h src/queue/queue_static_lib.c)

add_library(MagicOfTheC_iterator_lib STATIC src/linear_list/iterator/iterator.c
        src/linear_list/list/list.c
        src/linear_list/list/list.h)
# Create executable point
add_executable(MagicOfTheC_vector_bin src/vector/vector.c)
add_executable(MagicOfTheC_tree_bin src/tree/tree.c)
add_executable(MagicOfTheC_queue_dyn_bin src/queue/queue_dyn.c)
add_executable(MagicOfTheC_queue_static_bin src/queue/queue_arr.c)
add_executable(MagicOfTheC_list_bin src/linear_list/main.c)
add_executable(list_cycled src/linear_list_cycled/main.c
        src/linear_list_cycled/list/list.c
        src/linear_list_cycled/iterator/iterator.c)
add_executable(main src/meow/main.c)
add_executable(MagicOfTheC_exp_tree src/lab24/main.c)
# Link executable and library
target_link_libraries(MagicOfTheC_vector_bin MagicOfTheC_vector)
target_link_libraries(MagicOfTheC_tree_bin MagicOfTheC_tree_lib)
target_link_libraries(MagicOfTheC_list_bin MagicOfTheC_iterator_lib)
target_link_libraries(MagicOfTheC_queue_dyn_bin MagicOfTheC_queue_dyn_lib)
target_link_libraries(MagicOfTheC_queue_static_bin MagicOfTheC_queue_static_lib)
target_link_libraries(MagicOfTheC_exp_tree MagicOfTheC_exp_tree_libs)
add_library(merge_sort src/sort/merge_sort.c
        src/sort/merge_sort.h)
add_executable(lab26 src/lab26/main.c)
