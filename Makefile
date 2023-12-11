CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = minishell.c tokenizer.c tokenizer_list.c parser_tree.c parser.c parser_utils.c parser_tree_order.c print_test.c command_list.c command_list_utils.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
LIBFT_DIR = libft
LIBFT = libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline -lft -L./$(LIBFT_DIR)

$(OBJS) : %.o : %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

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
