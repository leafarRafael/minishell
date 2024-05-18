/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:08:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/18 14:14:40 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static int	ft_open(char *file);

int	open_in(t_mlst *mtrix, t_lst_line *lst)
{
	char	*infile;
	int		valid_open;

	valid_open = 0;
	infile = ft_cpy_lst_to_array(lst->lst);
	valid_open = ft_open(infile);
	ft_rmv_spcfc_lst_mtrx(mtrix, lst);
	free(infile);
	lst = NULL;
	return (valid_open);
}

static int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		return (-1);
	}
	if (fd != -1)
	{	
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2: ");
			return (-1);
		}
		close(fd);
	}
	return (0);
}
