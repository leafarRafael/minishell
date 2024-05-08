/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:44 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/08 15:43:47 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static int	ft_open(char *file);

int	open_appnd(t_mlst *mtrix, t_lst_line *lst)
{
	char	*infile;
	int		valid_open;

	valid_open = 0;
	infile = ft_cpy_lst_to_array(lst->lst);
	valid_open = ft_open(infile);
	ft_rmv_spcfc_lst_mtrx(mtrix, lst);
	lst = NULL;
	free(infile);
	return (valid_open);
}

static int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		return (-1);	
	}
	close(fd);
	return (1);
}
