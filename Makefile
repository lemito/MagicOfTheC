CC = gcc
CFLAGS = -Werror -Wpedantic

# Define the list of source files for each target
LIST_CYCLED_SRC = src/linear_list_cycled/main.c src/linear_list_cycled/list/list.c src/linear_list_cycled/iterator/iterator.c
QUEUE_DYN_SRC = src/queue/queue_dyn_bin.c src/queue/queue_dyn_lib.c src/queue/queue_dyn_lib.h

# Define the object files for each target
LIST_CYCLED_OBJ = $(LIST_CYCLED_SRC:.c=.o)
QUEUE_DYN_OBJ = $(QUEUE_DYN_SRC:.c=.o)

# Default target
all: list_cycled queue_dyn

# Target for list_cycled
list_cycled: $(LIST_CYCLED_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Target for queue_dyn
queue_dyn: $(QUEUE_DYN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Pattern rule for compiling .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
.PHONY: clean
clean:
	rm -f $(LIST_CYCLED_OBJ) $(QUEUE_DYN_OBJ) list_cycled queue_dyn

