NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc

CFLAGS = -g -ggdb3

SRCS = $(wildcard ./src/*.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

RM = rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -lreadline  -o $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

clean:
	@make --no-print-directory clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	@make --no-print-directory fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus .c.o
