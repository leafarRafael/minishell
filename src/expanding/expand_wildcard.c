/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:53:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/23 16:59:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

int	expand_whildcard(t_mlst *mlst)
{
	
}

t_mlst	*expand_asterisk(t_ast_n *cmd)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_mlst			*mlst;
	t_lst			*lst;

	dir = opendir("/home/rafael/minishell");
	if (dir == NULL)
	{
		ft_putstr_fd("cd: ", 2);
		ft_msg_error("/home/rafael/minishell", strerror(errno));
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