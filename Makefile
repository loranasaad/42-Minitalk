# Compiler & flags
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I include -I libft

# Source and object files
SRCS    := src/server/server_main.c
OBJS    := src/server/server_main.o

# Executable name
NAME    := server

# Default rule
all: $(NAME)

# Build libft first if needed
$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME)

# Compile each .c to .o (depends on your headers)
src/server/%.o: src/server/%.c include/minitalk.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning rules
clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re