BLUE	= \033[0;36m

NAME = libft.a

CC	=	cc

CFLAGS = -I../includes #-Wall -Wextra -Werror

SRCS = $(wildcard *.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

RM = rm -f

AR = ar rcs

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	@echo "$(BLUE)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(RM) $(OBJS) $(BONUS_OBJS)
	
clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

bonus:	all

.PHONY: all clean fclean re bonus
