/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:19:28 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/17 15:52:35 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>

# define SYNTAX_ERROR_CODE 258

typedef enum e_quote
{
	E_QUOTE = 0x01,
	E_DOUBLE_QUOTE = 0x02,
	E_ALL_QUOTE = 0x03,
}	t_quote;

typedef enum e_token
{
	T_SPA,
	T_TAB,
	T_NEWLINE,
	T_SEMICOLON,
	T_LPARE,
	T_RPARE,
	T_PIPE,
	T_AMPER,
	T_LESS,
	T_GREATER,
	T_OR,
	T_AND,
	T_HEREDOC,
	T_APPEND,
}	t_token;

typedef enum e_ptype
{
	P_EXPR,
	P_REDIRECTION,
	P_STATE,
	P_SUBCMD,
	P_CMD,
}	t_ptype;

typedef enum e_ctype
{
	C_CMD,
	C_INPUT,
	C_OUTPUT,
	C_HEREDOC,
	C_APPEND,
}	t_ctype;

typedef struct s_tokenlst
{
	int					type;
	char				*str;
	struct s_tokenlst	*next;
}	t_tokenlst;

typedef struct s_ptree
{
	int				type;
	char			*expr;
	struct s_ptree	*left;
	struct s_ptree	*right;
}	t_ptree;

typedef struct s_command
{
	int					type;
	char				**exprs;
	char				**infiles;
	int					*inflag;
	char				**outfiles;
	struct s_command	*next;
}	t_command;

typedef struct s_info
{
	char	*pwd;
	int		idx;
	int		cmd;
	int		*fd;
	pid_t	pid;
	char	**envp;
	char	**path;
	int		exit_code;
	int		fd_read;
	int		fd_write;
}	t_info;

t_tokenlst	*tokenizer_parse(char *str);

t_tokenlst	*tokenizer_list_create_node(int type, char *str);
void		tokenizer_list_add_node(t_tokenlst **list, t_tokenlst *node);
t_tokenlst	*tokenizer_list_get_node(t_tokenlst **list);
void		tokenizer_list_free_node(t_tokenlst *node);
void		*tokenizer_list_all_free(t_tokenlst **list);

t_ptree		*parser_tree_create_node(int type, char *expr);
void		parser_tree_node_free(t_ptree *tree);
void		*parser_tree_all_free(t_ptree *tree);
t_ptree		*parser_tree_make_root(int type, t_ptree *left, t_ptree *right);

t_ptree		*parser_cmd(t_tokenlst **lst);

int			parser_utils_check_type(int type, t_tokenlst *node);
char		*parser_utils_get_node_str(t_tokenlst *node);
int			parser_error(t_ptree *tree, t_tokenlst *list);

void		parser_tree_order(t_ptree *tree, t_command **pcmd, t_info *info);

t_command	*command_list_create_node(void);
void		command_list_add_node(t_command **list, t_command *node);
t_command	*command_list_get_node(t_command **list);
void		command_list_free_node(t_command *node);
void		command_list_all_free(t_command *list);

void		command_list_free_strs(char **strs);
void		command_list_add_expr(t_command **list, char *expr);
void		command_list_add_redirection(t_command **list, char *expr);

void		signal_readline_handler(int signo);
void		signal_heredoc_handler(int signo);
int			signal_cursor_save(void);
void		signal_setting(void (quit)(int), void (interrupt)(int));

void		delete_heredoc_files(t_command *cmd);
int			create_heredoc(t_command *cmd, t_info *info);

int			get_str_max_length(char *s1, char *s2);
char		*make_heredoc_file_name(void);
char		*make_limiter(t_command *cmd, int idx);

char		*heredoc_change_env(char *str, t_info *info);

int			heredoc_search(t_ptree *tree, t_info *info, int flag);

void		env_setting(t_info *info);

void		print_parser_tree(t_ptree *tree, int flag);
void		print_token_list(t_tokenlst *list);
void		print_command_list(t_command *list);

// excute/utils.c
int			err_seq(char *str, char *err, int ex, int flag);
int			ft_strcmp(const char *s1, const char *s2);
void		erase_vector(char ***arr, int i, int size, int flag);

// excute/unset.c
int			builtin_unset(char **cmd, t_info *info);

// excute/single_cmd.c
char		*cmd_path(t_info *info, char **cmd, int idx);
int			single_cmd(t_command *command, t_info *info);

// excute/pwd.c
int			builtin_pwd(char **cmd, t_info *info);

// excute/openfiles.c
int			get_fds(t_command *command, t_info *info, int in, int out);

// excute/multi_cmd.c
void		child(t_command *command, t_info *info);

// excute/export_with_arg.c
int			make_ev(t_info *info, char *arg);

// excute/export_no_arg.c
int			builtin_export(char **cmd, t_info *info);
void		sort_by_ascii(char **envp, int size);

// excute/exit.c
int			builtin_exit(char **cmd, t_info *info);

// excute/excute.c
int			execute(t_command *command, t_info *info);
void		close_pipe(t_info *info);
void		end_seq(t_info *info);

// excute/echo.c
int			builtin_echo(char **cmd, t_info *info);

// excute/builtin_env.c
int			builtin_env(char **cmd, t_info *info);

// excute/builtin_cd.c
int			builtin_cd(char **cmd, t_info *info);

// excute/extend_env.c
char		*env_to_str(t_info *info, char *str, char *ret, int len);
int			extend_env(t_command *command, t_info *info);

// excute/change_env.c
char		*cpy_env_str(t_info *info, char *str, char *ret, int len);
char		*cpy_normal_str(char *str, char *ret, int len);
int			return_env_len(char *str);
char		*change_env(char *str, t_info *info);

// excute/remove_quotes.c
char		*remove_quote(char *str, int flag);

// excute/wc_and_quotes.c
void		wc_and_quotes(t_command *cmd, int *idx);
int			wc_and_quotes_for_files(char **file, int f_nbr);

// excute/check_wc_arr.c
int			check_with_arr(t_command *command, char **arr, int *idx);
int			make_wc_arr(DIR *dir, char **arr, char ***wc);
int			check_last_wc(char *name, char *arr);

// excute/file_wc_env.c
int			check_file_name_with_arr(char **file, int f_nbr, char **arr);
int			check_file_name(t_info *info, char **file, int f_nbr);

// excute/make_wc_arr.c
int			make_wc_arr_normal(DIR *dir, char **arr, char ***wc);
int			make_wc_arr_hidden(DIR *dir, char **arr, char ***wc);
int			make_wc_arr_directory(DIR *dir, char **arr, char ***wc);

#endif