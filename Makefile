# -*- Makefile -*-

CSRCS = client.c utils.c

SSRCS = server.c

COBJS = $(CSRCS:.c=.o)

SOBJS = $(SSRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CLIENT = client

SERVER = server

all: $(CLIENT) $(SERVER)

$(CLIENT): $(COBJS) minitalk.h
	cc $(CFLAGS) $(COBJS) -o $@

$(SERVER): $(SOBJS) minitalk.h
	cc $(CFLAGS) $(SOBJS) -o $@

clean:
	rm -rf $(SOBJS) $(COBJS)

fclean: clean
	rm -rf $(CLIENT) $(SERVER)

re:	fclean $(CLIENT) $(SERVER)

.PHONY: all clean fclean re bonus