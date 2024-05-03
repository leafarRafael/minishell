/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:48:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/03 09:41:50 by rbutzke          ###   ########.fr       */
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

# define PATH "PATH=/"
# define SIZE_PATH 6

typedef struct s_variables_minishell
{
	t_mtrx_lst	*m_lst_env;
	t_lst		*input_lst;
	char		*input;
	char		**env;
	char		**temp_environ;
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

/*
			Function parse
*/
void			ft_scanner_input(t_lst *lst);
int				ft_have_operator(t_lst *lst);
void			ft_scanner_input(t_lst *lst);
int				ft_delete_cmatrix(char **matrix);
int				ft_define_cmd_status(t_mtrx_mtrx *m_m_lst);
int				ft_remove_cmd_status(t_mtrx_mtrx *m_m_lst);
void			ft_populetree(t_ast *tree, t_mtrx_mtrx *mtrx_mtrx);

void			ft_printf_matrix(char **matrix);
void			ft_print_array_lst(t_lst *lst, int front_back);
void			ft_print_array_lst_content_type(t_lst *lst);
void			show_str_type(int type);
void			print_all_type(void);
void			print_operator(t_lst *lst);
void			ft_print_matrix_line(t_mtrx_lst *m_line);
int				ft_separate_operators(t_mtrx_lst *matrix_lst,
					t_lst *input_user);
void			ft_print_lst_matrix(t_mtrx_mtrx *m_l);
void			ft_print_todos_os_tokens_expandidos(t_mtrx_mtrx *mtrx_mtrx);
void			ft_printtree(t_ast_node *root);

int				ft_input_is_valid(char *array);
int				ft_exit(char *input);
void			ft_free_memory_revert_environ(t_mini *v);
char			**ft_path_env(t_mtrx_lst *m_lst);
void			ft_execute(t_ast_node *cmd, t_mtrx_lst *env_list);
char			*ft_get_executable(char *command, char **path);

void			ft_open_outfile(char *file);
void			ft_pipe(int pipe[2]);
void			ft_pipe_parent(int pipe[2]);

void			ft_parse_and_execute(t_lst *input, t_mtrx_lst *mrtx_lst_env);


void			here_doc(t_mtrx_lst *mtrix);
void			ft_opens_all_input_files(t_mtrx_lst *mtrix);
void			ft_opens_all_output_files_append(t_mtrx_lst *mtrix);
void 			ft_opens_all_output_files_truncate(t_mtrx_lst *mtrix);



#endif