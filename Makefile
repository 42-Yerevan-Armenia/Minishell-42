RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[1;33m
RESET   = \033[0;37m
SKY     = \033[1;36m

NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

TMP = objs

CC = cc

CFLAGS = -I./includes -I$(HOME)/readline/include -Wall -Wextra -Werror

# Adjust the LINKER to dynamically detect the right directory for readline
#ifeq ($(HOME), /Users/vaghazar)
#    LINKER = -L./readline-vaghazar/lib -lreadline
#else ifeq ($(HOME), /Users/arakhurs)
#    LINKER = -L./readline-arakhurs/lib -lreadline
#else
    LINKER = -L$(HOME)/readline/lib -lreadline -lncurses
#endif

# Dynamically find source files
SRCS = $(shell find ./src -name "*.c" | grep src | grep '\.c')

OBJS_DIR = $(shell find ./src -name "*.c" | cut -d'/' -f4 | grep '\.c')
OBJS = $(patsubst %.c, ./$(TMP)/%.o, $(OBJS_DIR))

RM = rm -fr

# Prerequisites for the sources
PRER = ./src/execute ./src/parsing

# Rule for compiling source files
./$(TMP)/%.o: ./src/execute/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(YELLOW)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

./$(TMP)/%.o: ./src/parsing/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(YELLOW)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

# Default target
all: $(NAME)

$(NAME): $(TMP) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LINKER) $(OBJS) $(LIBFT) -o $(NAME)

$(TMP):
	@mkdir $(TMP)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ $(NAME) successfully created$(RESET)"

# Clean up temporary files
clean:
	@make --no-print-directory clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS_DIR)
	$(RM) $(TMP)
	@echo "$(RED)♨️  clean  🗑$(RESET)"

# Full clean, including the executable
fclean: clean
	@make --no-print-directory fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo "$(RED)♨️  fclean  🗑$(RESET)"

# Rebuild everything
re: fclean all

# Install the readline library if it doesn't exist
install_readline:
	@echo "$(YELLOW)💡 Installing GNU readline for $(USER)...$(RESET)"
	@wget ftp://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz || curl -O ftp://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz
	@tar xvfz readline-8.1.tar.gz
	@cd readline-8.1 && ./configure --prefix=$(HOME)/readline
	@cd readline-8.1 && make
	@cd readline-8.1 && make install
	@cd .. && rm -rf readline-8.1 readline-8.1.tar.gz
	@echo "$(GREEN)✅ GNU readline successfully installed for $(USER)!$(RESET)"

# Ensure Makefile is up to date for correct usage
.PHONY: all clean fclean re bonus .c.o install_readline
