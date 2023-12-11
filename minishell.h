/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:19:28 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/11 16:04:16 by sungyoon         ###   ########.fr       */
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
	char				**outfiles;
	struct s_command	*next;
}	t_command;

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

void		parser_tree_order(t_ptree *tree, t_command **pcmd);

t_command	*command_list_create_node(void);
void		command_list_add_node(t_command **list, t_command *node);
t_command	*command_list_get_node(t_command **list);
void		command_list_free_node(t_command *node);
void		command_list_all_free(t_command *list);

void		command_list_free_strs(char **strs);
void		command_list_add_expr(t_command **list, char *expr);
void		command_list_add_redirection(t_command **list, char *expr);

void		print_parser_tree(t_ptree *tree, int flag);
void		print_token_list(t_tokenlst *list);
void		print_command_list(t_command *list);

#endif