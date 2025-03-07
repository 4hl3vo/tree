CC := gcc
CFLAGS := -g -Wall -Wextra

bst:
	$(CC) $(CFLAGS) -o bst bst.c
avl:
	$(CC) $(CFLAGS) -o avl avl.c
red-black:
	$(CC) $(CFLAGS) -o red-black red-black.c
clean:
	rm -f tree bst avl red-black
