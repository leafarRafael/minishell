/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:26:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/07 10:40:17 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <dirent.h>

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

typedef enum s_builtin_size
{
	_BINARY = 0,
	_CD,
	_PWD,
	_ENV,
	_ECHO,
	_EXIT,
	_UNSET,
	_EXPORT
}			t_builtin_size;

typedef struct s_variables_builtins
{
	t_llst	*line;
	t_llst	*env;
	t_lst	*list;
	t_lst	*lst;
	t_node	*node;
	char	*prefix;
	char	*new_var;
	char	*nbr_exit;
	int		nbr;
	int		index;
	int		flag;
	int		i_color;
	t_ast	*expor_sort;

}			t_builtin;

int			is_builtin(t_ast_n *cmd);
void		cd(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		echo(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		env(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		my_exit(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		pwd(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		unset(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		ft_manager_fd_builtin(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		ft_valid_command_builtin(t_ast_n *cmd);
void		finished_builtin(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
char		*get_prfx(t_node *ptr, t_lst *lst);
int			ft_strlstcmp(t_lst *lst, char *str);
void		export(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
void		export_putenv(t_mini *mini);
void		export_addvar(t_ast_n *cmd, t_mini *mini);

#endif
