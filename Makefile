RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
RESET	= \033[0;37m
SKY		= \033[1;36m

NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc

CFLAGS = -g -ggdb3 -I./includes #-fsanitize=address

SRCS = $(wildcard ./src/*/*.c)
SRCS += $(wildcard ./src/*.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

RM = rm -f

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	@echo "$(YELLOW)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -lreadline  -o $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ $(NAME) sucessfully created$(RESET)"

clean:
	@make --no-print-directory clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS)
	@echo "$(RED)♨️  clean  🗑$(RESET)"

fclean: clean
	@make --no-print-directory fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo "$(RED)♨️  fclean  🗑$(RESET)"

re:	fclean all

.PHONY: all clean fclean re bonus .c.o
