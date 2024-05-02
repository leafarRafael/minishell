/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all_outfiles_trucate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:36 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/02 14:15:27 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_open_outfile_truncate(char *file);

void ft_opens_all_output_files_truncate(t_mtrx_lst *mtrix)
{
	t_lst_line	*current;
	t_lst_line	*next;
	char		*outfile;
	int			i;
	int			size;

	i = 1;
	current = mtrix->head;
	next = current->next;
	size = mtrix->size;
	while (i <= size)
	{
		if (current->rdrct == REDI_OUT)
		{
			outfile = ft_cpy_lst_to_array(current->lst);
			ft_open_outfile_truncate(outfile);
			ft_rmv_spcfc_lst_mtrx(mtrix, current);
			free(outfile);
		}
		i++;
		current = next;
		next = next->next;
	}
}

static void	ft_open_outfile_truncate(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
	if (fd == -1)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}