/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:21:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/22 14:25:44 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

int	ft_cd(t_ast_n *cmd)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*dir_name;

	dir = opendir("/nfs/homes/rbutzke/minishell/Makefile");
	if (dir == NULL)
	{
		ft_putstr_fd("cd: ", 2);
		ft_msg_error("/nfs/homes/rbutzke/minishell/Makefile", strerror(errno));
		return (-1);
	}
	while (1)
	{
		dirent = readdir(dir);
		if (dirent == NULL)
			break ;
		printf("%s", dirent->d_name);
	}
	return (1);
}

t_mlst	*expand_asterisk(t_ast_n *cmd)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_mlst			*mlst;
	t_lst			*lst;

	dir = opendir("/nfs/homes/rbutzke/minishell");
	if (dir == NULL)
	{
		ft_putstr_fd("cd: ", 2);
		ft_msg_error("/nfs/homes/rbutzke/minishell", strerror(errno));
		return (NULL);
	}
	mlst = init_mlst();
	while (1)
	{
		dirent = readdir(dir);
		if (dirent == NULL)
			break ;
		lst = ft_init_lst();
		ft_add_string_in_list(lst, dirent->d_name);
		ft_add_list_back(mlst, lst);
		lst = NULL;
	}
	ft_print_matrix_line(mlst);
	closedir(dir);
	return (mlst);
}