/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_trucate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:36 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 08:29:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static void	ft_open(char *file);

void	ft_opens_truncate(t_mlst *mtrix, t_lst_line *lst)
{
	char	*outfile;

	outfile = ft_cpy_lst_to_array(lst->lst);
	ft_open(outfile);
	ft_rmv_spcfc_lst_mtrx(mtrix, lst);
	free(outfile);
}

static void	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
	if (fd == -1)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
