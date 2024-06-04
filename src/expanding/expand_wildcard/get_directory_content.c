/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_directory_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:57:34 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 09:57:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

static DIR	*getdir(char *path);

t_mlst	*expand_current_directory(void)
{
	char	*dir_path;
	t_mlst	*directory_contents;

	dir_path = (char *)getdir_list_string(STRING);
	if (!dir_path)
		return (NULL);
	directory_contents = read_directory(dir_path);
	if (!directory_contents)
		return (NULL);
	free(dir_path);
	return (directory_contents);
}

t_mlst	*read_directory(char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_mlst			*mlst;
	t_lst			*lst;

	dir = getdir(path);
	if (!dir)
		return (NULL);
	mlst = init_mlst();
	while (1)
	{
		dirent = readdir(dir);
		if (dirent == NULL)
			break ;
		if (dirent->d_name[0] != '.')
		{
			lst = ft_init_lst();
			ft_add_string_in_list(lst, dirent->d_name);
			ft_scanner_add_literal(lst);
			ft_add_list_back(mlst, lst);
			lst = NULL;
		}
	}
	closedir(dir);
	return (mlst);
}

static DIR	*getdir(char *path)
{
	DIR	*dir;

	if (!path)
		return (NULL);
	dir = opendir(path);
	if (dir == NULL)
	{
		ft_msg_error(path, strerror(errno));
		return (NULL);
	}
	return (dir);
}
