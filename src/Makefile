CC = gcc
CFLAGS = -static -Wall -Wextra
OBJS = main.o minishell.o ramsayboy.o
DEPS = parser.h minishell.h ramsayboy.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

minishell: $(OBJS) libparser.a
	$(CC) $(CFLAGS) $^ -o $@

#minishell: $(OBJS) libparser.a
#	$(CC) $(CFLAGS) $< -o $@ -L. -lparser

.PHONY: clean
clean:
	rm -rf *.o