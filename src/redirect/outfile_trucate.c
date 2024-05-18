/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_trucate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:36 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/17 13:26:09 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static int	ft_open(char *file);

int	open_trnc(t_mlst *mtrix, t_lst_line *lst)
{
	char	*outfile;
	int		valid_open;

	valid_open = 0;
	outfile = ft_cpy_lst_to_array(lst->lst);
	valid_open = ft_open(outfile);
	ft_rmv_spcfc_lst_mtrx(mtrix, lst);
	free(outfile);
	return (valid_open);
}

static int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror ("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}
