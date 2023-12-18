CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = minishell.c \
tokenizer.c tokenizer_list.c \
parser.c parser_utils.c \
parser_tree.c parser_tree_order.c \
command_list.c command_list_utils.c \
print_test.c \
signal_process.c \
heredoc.c heredoc_utils.c heredoc_env.c heredoc_search.c \
env_setting.c \
./excute/builtin_cd.c ./excute/builtin_env.c ./excute/echo.c ./excute/excute.c \
./excute/exit.c ./excute/export_no_arg.c ./excute/export_with_arg.c ./excute/multi_cmd.c \
./excute/openfiles.c ./excute/pwd.c ./excute/single_cmd.c ./excute/unset.c ./excute/utils.c \
./excute/extend_env.c ./excute/change_env.c ./excute/remove_quote.c ./excute/wc_and_quotes.c \
./excute/check_wc_arr.c ./excute/file_wc_env.c ./excute/make_wc_arr.c
SRCS_B = ./bonus/minishell_bonus.c \
./bonus/tokenizer_bonus.c ./bonus/tokenizer_list_bonus.c \
./bonus/parser_bonus.c ./bonus/parser_utils_bonus.c \
./bonus/parser_tree_bonus.c ./bonus/parser_tree_order_bonus.c \
./bonus/command_list_bonus.c ./bonus/command_list_utils_bonus.c \
./bonus/print_test_bonus.c \
./bonus/signal_process_bonus.c \
./bonus/heredoc_bonus.c ./bonus/heredoc_utils_bonus.c ./bonus/heredoc_env_bonus.c ./bonus/heredoc_search_bonus.c \
./bonus/env_setting_bonus.c \
./bonus/builtin_cd_bonus.c ./bonus/builtin_env_bonus.c ./bonus/echo_bonus.c ./bonus/excute_bonus.c \
./bonus/exit_bonus.c ./bonus/export_no_arg_bonus.c ./bonus/export_with_arg_bonus.c ./bonus/multi_cmd_bonus.c \
./bonus/openfiles_bonus.c ./bonus/pwd_bonus.c ./bonus/single_cmd_bonus.c ./bonus/unset_bonus.c ./bonus/utils_bonus.c \
./bonus/extend_env_bonus.c ./bonus/change_env_bonus.c ./bonus/remove_quote_bonus.c ./bonus/wc_and_quotes_bonus.c \
./bonus/check_wc_arr_bonus.c ./bonus/file_wc_env_bonus.c ./bonus/make_wc_arr_bonus.c
OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)
NAME = minishell
NAME_B = minishell_bonus
LIBFT_DIR = libft
LIBFT = libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline -lft -L./$(LIBFT_DIR)

bonus : FLAG_FILE

FLAG_FILE : $(OBJS_B)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME_B) $^ -lreadline -lft -L./$(LIBFT_DIR)
	touch $@

$(OBJS): %.o : %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_B): %.o : %.c ./bonus/minishell_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	rm -f $(OBJS_B)
	rm -f FLAG_FILE

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(NAME_B)

re : 
	make fclean
	make all

.PHONY : all clean fclean re bonus
