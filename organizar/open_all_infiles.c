/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all_infiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:08:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/02 14:11:21 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_open_infile(char *file);

void ft_opens_all_input_files(t_mtrx_lst *mtrix)
{
	t_lst_line	*current;
	t_lst_line	*next;
	char		*infile;
	int			i;
	int			size;

	i = 1;
	current = mtrix->head;
	next = current->next;
	size = mtrix->size;
	while (i <= size)
	{
		if (current->rdrct == REDI_IN)
		{
			infile = ft_cpy_lst_to_array(current->lst);
			ft_open_infile(infile);
			ft_rmv_spcfc_lst_mtrx(mtrix, current);
			free(infile);
		}
		i++;
		current = next;
		next = next->next;
	}
}

static void	ft_open_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}