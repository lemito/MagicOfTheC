CC = gcc
CFLAGS = -Werror -Wpedantic

all: 
	list_cycled

list_cycled: src/linear_list_cycled/main.c src/linear_list_cycled/list/list.c src/linear_list_cycled/iterator/iterator.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f list_cycled
