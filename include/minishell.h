/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:48:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 17:38:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int status_child;

# include "abstract_syntax_tree.h"
# include "array_lst.h"
# include "expanding.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "key_words.h"
# include "libft.h"
# include "matrix_lst.h"
# include "matrix_matrix_lst.h"
# include "parser.h"
# include "scanner.h"
# include "string.h"
# include "token.h"
# include "redirect.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>

# define PROGRAM_NAME "minishell: "
# define PATH "PATH=/"
# define SIZE_PATH 6
# define PATH_HERE_DOC "<< tmp/0000"

typedef struct s_variables_minishell
{
	t_mmlst		*mmlst;
	t_mlst		*m_lst_env;
	t_lst		*input_lst;
	char		**env;
	char		**temp_environ;
	int			fd_std[2];
}				t_mini;

typedef struct s_var_executable
{
	char		*path_exe;
	char		**env;
	char		**command_m;
	pid_t		pid;
	int			tube[2];
}				t_var_exe;

typedef enum s_here_doc
{
	UNIT = 0,
	TEN = 1,
	HUNDRED = 2,
	THOUSAND = 3
}	t_here_doc;

typedef enum s_cpy_restore
{
	COPY = 0,
	RESTORE = 1
}	t_cpy_restore;

/*
			Function parse
*/
void			ft_scanner_input(t_lst *lst);
int				ft_have_operator(t_lst *lst);
void			ft_scanner_input(t_lst *lst);
int				ft_delete_cmatrix(char **matrix);
int				ft_define_cmd_status(t_mmlst *m_m_lst);
int				ft_remove_cmd_status(t_mmlst *m_m_lst);
void			ft_define_ast(t_ast *tree, t_mmlst *mmlst);
void			ft_populetree_right(t_ast *tree, t_mmlst *mmlst);

void			ft_printf_matrix(char **matrix);
void			ft_print_array_lst_content_type(t_lst *lst);
void			show_str_type(int type);
void			print_all_type(void);
void			print_operator(t_lst *lst);
int				ft_separate_operators(t_mlst *matrix_lst,
					t_lst *input_user);
void			ft_print_lst_matrix(t_mmlst *m_l);
void			ft_print_todos_os_tokens_expandidos(t_mmlst *mtrx_mtrx);
void			ft_printtree(t_ast_n *root);

int				ft_input_is_valid(char *array);
int				ft_exit(char *input);
void			ft_free_memory_revert_environ(t_mini *v);
char			**ft_path_env(t_mlst *m_lst);

void			ft_pipe(int pipe[2]);
void			ft_pipe_parent(int pipe[2]);



void	ft_parse_exe(t_lst *input, t_mini *mini);

void 	free_memory(t_mini *mini, t_var_exe *var, t_ast *ast, int status_exit);
void	ft_msg_error(char *invalid_input, char *msg_error);
/*
		FUNCTION IN SRC/EXECUTE_COMMAND
*/
void	ft_call_and_exec_manager(t_ast_n *cmd, t_mini *mini, t_ast *ast);
void	ft_expand_subshell(t_ast_n *cmd, t_mini *mini, t_ast *ast);
char	*ft_get_executable(t_mini *mini, t_var_exe *var, t_ast *ast);

void	ft_exec_manager(t_ast_n *cmd, t_mini *mini, t_ast *ast);
void	children(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
void	parent(t_ast_n *cmd, t_mini *mini, t_var_exe *var);

// BUILTIN
int	ft_valid_builtin(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
// ENV
void	ft_env(t_mini *mini);
void	ft_print_array_lst(t_lst *lst);
void	ft_print_matrix_line(t_mlst *m_line);


#endif
