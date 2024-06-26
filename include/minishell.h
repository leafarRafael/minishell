/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:48:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 15:19:39 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "abstract_syntax_tree.h"
# include "array_lst.h"
# include "color.h"
# include "expanding.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "key_words.h"
# include "libft.h"
# include "matrix_lst.h"
# include "matrix_matrix_lst.h"
# include "parser.h"
# include "redirect.h"
# include "scanner.h"
# include "string.h"
# include "token.h"
# include "collector.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <wait.h>
# define PROGRAM_NAME "\033[34m minishell$ \033[0m"
# define PATH "PATH=/"
# define SIZE_PATH 6
# define PATH_HERE_DOC "<< /tmp/0000"

extern int	g_status_child;

typedef struct s_variables_minishell
{
	t_mmlst	*mmlst;
	t_mlst	*m_lst_env;
	t_lst	*input_lst;
	t_clct	*collect;
	t_clct	*collect_ast;
	char	*input;
	char	**env;
	char	**temp_environ;
	char	**color;
	int		i_color;
	int		fd_std[2];
	int		status;
}			t_mini;

typedef struct s_var_executable
{
	char	*path_exe;
	char	**env;
	char	**command_m;
	pid_t	pid;
	int		tube[2];
}			t_var_exe;

typedef enum s_here_doc
{
	UNIT = 0,
	TEN = 1,
	HUNDRED = 2,
	THOUSAND = 3
}			t_here_doc;

typedef enum s_cpy_restore
{
	COPY = 0,
	RESTORE = 1,
	SWAP = 2
}			t_cpy_restore;

typedef enum s_boolean
{
	FALSE = 0,
	TRUE = 1
}			t_boolean;

typedef enum s_string_or_lst
{
	STRING = 0,
	LIST,
}			t_strlst;

typedef enum s_sufix_prefix
{
	SUFFIX = 0,
	PREFIX,
}			t_sufix_prefix;

/*
			Function parse
*/
void		ft_scanner_input(t_lst *lst);
void		ft_scanner_input(t_lst *lst);
int			ft_delcmtrx(char **matrix);
int			ft_define_cmd_status(t_mmlst *m_m_lst);
int			ft_remove_cmd_status(t_mmlst *m_m_lst);
void		command_call_structure(t_ast *tree, t_mmlst *mmlst);
void		ft_populetree_right(t_ast *tree, t_mmlst *mmlst);

int			ft_input_is_valid(char *array);
void		ft_free_memory_revert_environ(t_mini *v);
char		**path_system_bin(t_mlst *m_lst);

void		builds_execution_call(t_mini *mini);

void		free_memory(t_mini *mini, t_var_exe *var, int status_exit);
void		ft_msg_error(char *invalid_input, char *msg_error);
void		ft_msg_error_lst(char *function, t_lst *input_lst, char *msg_error);

void		ft_call_and_exec_manager(t_ast_n *cmd, t_mini *mini);
void		ft_expand_subshell(t_ast_n *cmd, t_mini *mini);
char		*ft_get_executable(t_mini *mini, t_var_exe *var);

void		ft_exec_manager(t_ast_n *cmd, t_mini *mini);
void		binary(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		parent(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		subshell(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		setup_command(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		free_cmd_operator_executed(t_ast_n *cmd, t_mini *mini);

void		ft_remove_quote_mlst(t_mlst *mlst);
void		ft_remove_quotes_lst(t_lst *lst);

int			ft_valid_syntax_open_here_doc(t_lst *lst);
void		swap_tty(int copy_restore, t_mini *mini);
void		close_allfd(t_mini *mini);

void		ft_swap_environ(t_mini *mini, int swap_restore);

t_mlst		*expand_asterisk(t_ast_n *cmd);
void		*getdir_list_string(int str_lst);
char		*ft_get_program_name(void);
void		ft_wait_execution(t_mini *mini);
void		execute(t_ast_n *cmd, t_mini *mini, t_var_exe *var);

#endif
