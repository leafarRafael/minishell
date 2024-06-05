/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:55:33 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 12:10:53 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

char	*ft_mtrx_to_str(char **mtrx);
int		addcolor_matrix(char **mtrix);
int		add_prefix_or_sufix_to_matrix(char **matrix,
			char *prefix_suffix, int pre_su_fix);
char	**cpy_mtrx_add_prefix_sufix(char **matrix,
			char *prefix_suffix, int pre_su_fix);

char	*ft_get_program_name(void)
{
	char	**path_name;
	char	*directory;
	char	*path;
/* 	char	*program_name; */

	directory = (char *) getdir_list_string(STRING);
	if (!directory)
		return (NULL);
	path_name = ft_split(directory, '/');
	if (!path_name)
		return (NULL);
	if (add_prefix_or_sufix_to_matrix(path_name, "/", SUFFIX))
		return (NULL);
	if (addcolor_matrix(path_name))
		return (NULL);
	path = ft_mtrx_to_str(path_name);
/* 	program_name = ft_strjoin(path, PROGRAM_NAME); */
	ft_delcmtrx(path_name);
	free(directory);
/* 	free(path); */
	return (path);
}

char	**cpy_mtrx_add_prefix_sufix(char **matrix,
				char *prefix_suffix, int pre_su_fix)
{
	int		i;
	int		size;
	char	**new_matrix;

	i = 0;
	size = ft_mtrxlen(matrix)+1;
	new_matrix = ft_calloc(sizeof(char *), size);
	if (!new_matrix)
		return (NULL);
	while (matrix[i])
	{
		if (pre_su_fix == PREFIX)
			new_matrix[i] = ft_strjoin(prefix_suffix, matrix[i]);
		if (pre_su_fix == SUFFIX)
			new_matrix[i] = ft_strjoin(matrix[i], prefix_suffix);
		if (!new_matrix[i])
			return (NULL);
		i++;
	}
	return (new_matrix);
}

int	add_prefix_or_sufix_to_matrix(char **matrix,
			char *prefix_suffix, int pre_su_fix)
{
	int		i;
	char	*new_str;

	i = 0;
	while (matrix[i])
	{
		new_str = ft_strdup(matrix[i]);
		if (!new_str)
			return (1);
		free(matrix[i]);
		if (pre_su_fix == SUFFIX)
			matrix[i] = ft_strjoin(new_str, prefix_suffix);
		if (pre_su_fix == PREFIX)
			matrix[i] = ft_strjoin(prefix_suffix, new_str);
		if (!matrix[i])
			return (1);
		free(new_str);
		i++;
	}
	return (0);
}

int	addcolor_matrix(char **mtrix)
{
	char	**color;
	char	*new_str;
	int		i;
	int		i_color;

	color = ft_init_color();
	if (!color)
		return (1);
	i = 0;
	i_color = 0;
	while (mtrix[i])
	{
		new_str = ft_strjoin(color[i_color], mtrix[i]);
		free(mtrix[i]);
		mtrix[i] = ft_strjoin(new_str, RESET);
		if (!mtrix[i] || !new_str)
			return (1);
		free(new_str);
		if (i_color == 6)
			i_color = 0;
		i_color++;
		i++;
	}
	ft_delcmtrx(color);
	return (0);
}

char	*ft_mtrx_to_str(char **mtrx)
{
	char	*new_str;
	char	*temp;
	int		i;

	i = 1;
	new_str = ft_strdup(mtrx[0]);
	if (!new_str)
		return (NULL);
	while (mtrx[i])
	{
		temp = ft_strjoin(new_str, mtrx[i]);
		free(new_str);
		new_str = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (new_str);
}
