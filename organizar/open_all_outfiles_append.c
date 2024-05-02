/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all_outfiles_append.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:44 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/02 14:21:29 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_open_outfile_append(char *file);

void	ft_opens_all_output_files_append(t_mtrx_lst *mtrix)
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
		if (current->rdrct == APPEND)
		{
			outfile = ft_cpy_lst_to_array(current->lst);
			ft_open_outfile_append(outfile);
			ft_rmv_spcfc_lst_mtrx(mtrix, current);
			free(outfile);
		}
		i++;
		current = next;
		next = next->next;
	}
}

static void	ft_open_outfile_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	if (fd == -1)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
