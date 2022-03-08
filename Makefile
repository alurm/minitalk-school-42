CFLAGS := -Wall -Werror -Wextra

.PHONY: all
all: server client

.PHONY: bonus
bonus: server client

server: $(if $(findstring bonus, $(MAKECMDGOALS)), server_bonus.c, server.c)
	cc $(CFLAGS) -o $@ $^

client: $(if $(findstring bonus, $(MAKECMDGOALS)), client_bonus.c, client.c)
	cc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:

.PHONY: fclean
fclean: clean
	rm -rf server client

.PHONY: re
re: fclean all
