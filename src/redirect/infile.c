/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:08:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/04 16:55:06 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static void	ft_open(char *file);

void	ft_open_infile(t_mtrx_lst *mtrix, t_lst_line *lst)
{
	char	*infile;

	infile = ft_cpy_lst_to_array(lst->lst);
	ft_open(infile);
	ft_rmv_spcfc_lst_mtrx(mtrix, lst);
	free(infile);
}

static void	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
