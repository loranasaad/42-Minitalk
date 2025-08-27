CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I include

NAME_SERVER := server
NAME_CLIENT := client

NAME_SERVER_BONUS := server_bonus
NAME_CLIENT_BONUS := client_bonus

SRCS_SERVER := src/server/server_main.c src/common/utils.c
SRCS_CLIENT := src/client/client_main.c src/common/utils.c

OBJS_SERVER := $(SRCS_SERVER:.c=.o)
OBJS_CLIENT := $(SRCS_CLIENT:.c=.o)

SRCS_SERVER_BONUS := src/server/server_bonus.c src/common/utils_bonus.c
SRCS_CLIENT_BONUS := src/client/client_bonus.c src/common/utils_bonus.c

OBJS_SERVER_BONUS := $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS := $(SRCS_CLIENT_BONUS:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) -o $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re