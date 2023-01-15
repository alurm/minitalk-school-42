CFLAGS := -Wall -Werror -Wextra

.PHONY: all
all: server client

server: server.c
	cc $(CFLAGS) -o $@ $^

client: client.c
	cc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf server client

.PHONY: re
re: clean all
