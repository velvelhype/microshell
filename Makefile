NAME = microshell
CC = gcc
# CFLAGS = -Werror -Wall -Wextra 
#CFLAGS = -Werror -Wall -Wextra -g -fsanitize=thread
# CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address
SRCS = *.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all