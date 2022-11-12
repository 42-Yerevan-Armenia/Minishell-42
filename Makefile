RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
RESET	= \033[0;37m
SKY		= \033[1;36m

NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

TMP = objs

CC = cc

CFLAGS =  -I./includes  -I./readline-vaghazar/include  -fsanitize=address#-Wall -Wextra -Werror -g -ggdb3   #  

ifeq ($(HOME), /Users/vaghazar)
LINKER = -L ./readline-vaghazar/lib/ -lreadline
else ifeq ($(HOME), /Users/arakhurs)
LINKER = -L ./readline-arakhurs/lib
endif

SRCS = $(shell find ./src -name "*.c" | grep src | grep '\.c')

OBJS_DIR = $(shell find ./src -name "*.c" | cut -d'/' -f4 | grep '\.c')
OBJS = $(patsubst %.c, ./$(TMP)/%.o, $(OBJS_DIR))

RM = rm -fr

PRER = ./src/execute ./src/parsing

./$(TMP)/%.o: ./src/execute/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< 
	@echo "$(YELLOW)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

./$(TMP)/%.o: ./src/parsing/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< 
	@echo "$(YELLOW)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

all: $(NAME)

$(NAME): $(TMP) $(OBJS) $(LIBFT) 
	@$(CC) $(CFLAGS) $(LINKER) $(OBJS) -lreadline  $(LIBFT)  -o $(NAME)

$(TMP):
	@mkdir $(TMP)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ $(NAME) sucessfully created$(RESET)"

clean:
	# @make --no-print-directory clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS_DIR)
	$(RM) $(TMP)
	@echo "$(RED)♨️  clean  🗑$(RESET)"

fclean: clean
	# @make --no-print-directory fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo "$(RED)♨️  fclean  🗑$(RESET)"

re:	fclean all

.PHONY: all clean fclean re bonus .c.o
