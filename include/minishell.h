/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:48:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/14 11:26:24 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "redirect.h"


# define PATH "PATH=/"
# define SIZE_PATH 6
# define PATH_HERE_DOC "<< tmp/0000"

typedef struct s_variables_minishell
{
	t_mmlst		*mmlst;
	t_mlst		*m_lst_env;
	t_lst		*input_lst;
	char		*input;
	char		**env;
	char		**temp_environ;
	int			fd_std[2];
}				t_mini;

typedef struct s_var_executable
{
	char		*path_exe;
	char		*infile;
	char		*outfile;
	char		**env;
	char		**command_m;
	pid_t		pid;
	int			pipe[2];
}				t_var_exe;

typedef enum s_here_doc
{
	UNIT = 0,
	TEN = 1,
	HUNDRED = 2,
	THOUSAND = 3

}	t_here_doc;

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
void			ft_print_array_lst(t_lst *lst, int front_back);
void			ft_print_array_lst_content_type(t_lst *lst);
void			show_str_type(int type);
void			print_all_type(void);
void			print_operator(t_lst *lst);
void			ft_print_matrix_line(t_mlst *m_line);
int				ft_separate_operators(t_mlst *matrix_lst,
					t_lst *input_user);
void			ft_print_lst_matrix(t_mmlst *m_l);
void			ft_print_todos_os_tokens_expandidos(t_mmlst *mtrx_mtrx);
void			ft_printtree(t_ast_n *root);

int				ft_input_is_valid(char *array);
int				ft_exit(char *input);
void			ft_free_memory_revert_environ(t_mini *v);
char			**ft_path_env(t_mlst *m_lst);
char			*ft_get_executable(char *command, char **path);

void			ft_pipe(int pipe[2]);
void			ft_pipe_parent(int pipe[2]);

void	ft_execute(t_ast_n *cmd, t_mini *mini, t_ast *ast);
void	ft_parse_exe(t_lst *input, t_mini *mini);

int		free_memory(t_mini *mini, t_var_exe	*var, t_ast *ast);

#endif