CC = gcc
CFLAGS = -Werror -Wpedantic


LIST_CYCLED_SRC = src/linear_list_cycled/main.c src/linear_list_cycled/list/list.c src/linear_list_cycled/iterator/iterator.c
QUEUE_DYN_SRC = src/queue/queue_dyn_bin.c src/queue/queue_dyn_lib.c src/queue/queue_dyn_lib.h
QUEUE_STATIC_SRC = src/queue/queue_static_lib.h src/queue/queue_static_lib.c
MERGE_SORT_SRC = src/sort/merge_sort.h src/sort/merge_sort.c
LAB26_SRC = src/lab26/main.c

LIST_CYCLED_OBJ = $(LIST_CYCLED_SRC:.c=.o)
QUEUE_DYN_OBJ = $(QUEUE_DYN_SRC:.c=.o)
QUEUE_STATIC_OBJ = $(QUEUE_STATIC_SRC:.c=.o)
MERGE_SORT_OBJ = $(MERGE_SORT_SRC:.c=.o)
LAB26_OBJ = $(LAB26_SRC:.c=.o)


all: list_cycled queue_dyn lab26

list_cycled: $(LIST_CYCLED_OBJ)
	$(CC) $(CFLAGS) $^ -o $@.out

queue_dyn: $(QUEUE_DYN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@.out

lab26: $(QUEUE_STATIC_OBJ) $(MERGE_SORT_OBJ) $(LAB26_OBJ)
	$(CC) $(CFLAGS) $^ -o $@.out

gmp_example:
	gcc $(CFLAGS) src/BigAlgebra/gmp_example.cpp -o $@.out -lgmp -lgmpxx
	./gmp_example.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
.PHONY: clean
clean:
	rm -f *.o *.out

