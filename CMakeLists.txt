cmake_minimum_required(VERSION 3.27)
project(MagicOfTheC LANGUAGES C CXX)

# Set C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Add custom module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find required libraries
find_package(GMP REQUIRED)
find_library(UUID_LIBRARIES uuid)
find_path(UUID_INCLUDE_DIRS uuid/uuid.h)

# Define libraries
add_library(MagicOfTheC_vector STATIC src/vector/vector_lib.c)
add_library(MagicOfTheC_exp_tree_libs STATIC
    src/lab24/stack.c
    src/lab24/stack.h
    src/lab24/symbol.h
    src/lab24/token.h
    src/lab24/tree.h
)
add_library(MagicOfTheC_tree_lib STATIC src/tree/tree_lib.c)
add_library(MagicOfTheC_queue_dyn_lib STATIC src/queue/queue_dyn_lib.c)
add_library(MagicOfTheC_queue_static_lib STATIC
    src/queue/queue_static_lib.h
    src/queue/queue_static_lib.c
)
add_library(merge_sort STATIC
    src/sort/merge/merge_sort.c
    src/sort/merge/merge_sort.h
)
add_library(heap_sort STATIC
    src/sort/heap/heap_sort.c
    src/sort/heap/heap_sort.h
)
add_library(MagicOfTheC_binary_search_lib STATIC
    src/search/binary_search.h
    src/search/binary_search.c
)

# Define executables
add_executable(lab26 src/lab26/main.c)
add_executable(MagicOfTheC_vector_bin src/vector/vector.c)
add_executable(MagicOfTheC_tree_bin src/tree/tree.c)
add_executable(MagicOfTheC_queue_dyn_bin src/queue/queue_dyn.c)
add_executable(MagicOfTheC_queue_static_bin src/queue/queue_arr.c)
add_executable(list_cycled
    src/linear_list_cycled/main.c
    src/linear_list_cycled/list/list.c
    src/linear_list_cycled/iterator/iterator.c
)
add_executable(main src/meow/main.c)

add_executable(dequeue src/dequeue/main.c)
target_link_libraries(dequeue MagicOfTheC_vector)


add_executable(kp9 src/kp9/main.c src/kp9/table.h src/kp9/table.c)
add_executable(MagicOfTheC_exp_tree src/lab24/main.c)
add_executable(stress26 src/lab26/stress.c)
add_executable(BigAlgebra_vector src/BigAlgebra/on_vectors.cpp)
add_executable(BigAlegra_gmp src/BigAlgebra/gmp_example.cpp)
add_executable(BigAlegra_new
    src/BigAlgebra/new_algo.c
    src/BigAlgebra/new_algo.cpp
)
add_executable(HashTable src/HashTable/main.c)

# Link libraries to executables
target_link_libraries(MagicOfTheC_vector_bin MagicOfTheC_vector)
target_link_libraries(MagicOfTheC_tree_bin MagicOfTheC_tree_lib)
target_link_libraries(MagicOfTheC_queue_dyn_bin MagicOfTheC_queue_dyn_lib)
target_link_libraries(MagicOfTheC_queue_static_bin MagicOfTheC_queue_static_lib)
target_link_libraries(MagicOfTheC_exp_tree MagicOfTheC_exp_tree_libs)
target_link_libraries(lab26 merge_sort MagicOfTheC_queue_static_lib)
target_link_libraries(stress26 merge_sort MagicOfTheC_queue_static_lib)
target_link_libraries(kp9 heap_sort MagicOfTheC_binary_search_lib)
target_link_libraries(BigAlegra_gmp gmp gmpxx)

target_include_directories(HashTable PRIVATE ${UUID_INCLUDE_DIRS})
target_link_libraries(HashTable PRIVATE ${UUID_LIBRARIES})


add_executable(Deikstra src/Deikstra/Deikstra.c)

add_executable(polymorphism_NotTypesPoiners src/polymorphism/main2.c)
target_link_libraries(polymorphism_NotTypesPoiners m)

add_executable(classes src/polymorphism/main3.c)
add_executable(AVLtree src/AVLtree/main.c)
add_executable(SparceMatrix src/SparceMatrix.cpp)

add_subdirectory(src/cpp)
add_subdirectory(src/algo)


add_subdirectory(src/stepik)
add_executable(qsort_9 src/stepik/12/qsort_9.c)
add_executable(struct_card src/stepik/8/struct_card.c)
add_executable(elong_print src/stepik/8/elong_print.c)
add_executable(elong_add src/stepik/8/elong_add.c)
add_executable(elong_add2 src/stepik/14/elong_add2.c)
add_executable(elong_add3 src/stepik/14/elong_add3.c)
add_executable(toLongN src/stepik/14/toLongN.c)
