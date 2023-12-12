CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = minishell.c tokenizer.c tokenizer_list.c parser_tree.c parser.c parser_utils.c parser_tree_order.c print_test.c command_list.c command_list_utils.c \
./excute/builtin_cd.c ./excute/builtin_env.c ./excute/echo.c ./excute/excute.c \
./excute/exit.c ./excute/export_no_arg.c ./excute/export_with_arg.c ./excute/multi_cmd.c \
./excute/openfiles.c ./excute/pwd.c ./excute/single_cmd.c ./excute/unset.c ./excute/utils.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
LIBFT_DIR = libft
LIBFT = libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline -lft -L./$(LIBFT_DIR)

$(OBJ): $(SRCS)
	$(CC) $(CFLAGS) -c $^

clean :
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re
