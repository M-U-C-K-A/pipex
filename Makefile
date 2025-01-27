NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

RM = rm -rf

SRCS = 	src/pipex.c\
		src/utils.c\
		libft/libft.a\

BONUS_SRCS = 	src_bonus/pipex_bonus.c\
				src_bonus/utils_bonus.c\
				libft/libft.a\

$(NAME) :
	@echo "\033[32m[ Compiling ] \033[0m"
	make all -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "\033[32m[ Compilation done ] \033[0m"

bonus :
	@echo "\033[32m[ Compiling Bonus ] \033[0m"
	make all -C libft
	gcc $(CFLAGS) $(BONUS_SRCS) -o $(NAME)_bonus
	@echo "\033[32m[ Bonus Compilation done ] \033[0m"

all : $(NAME)

fclean : clean
	@echo "\033[31m[ Removing executable ] \033[0m"
	$(RM) $(NAME) $(NAME)_bonus
	make fclean -C libft

clean :
	@echo "\033[31m[ Removing objects ] \033[0m"
	$(RM) $(NAME) $(NAME)_bonus
	make clean -C libft

re : fclean all

.PHONY : all clean fclean re bonus

