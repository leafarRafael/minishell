/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:05:47 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/06 09:58:47 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "expanding.h"

static void	ft_open(t_lst *lst);
static t_mtrx_lst	*ft_read_std(t_lst *lst);

void	ft_open_here_doc(t_mtrx_lst *mtrix, t_lst_line *lst)
{
	ft_open(lst->lst);
	ft_rmv_spcfc_lst_mtrx(mtrix, lst);
}

static void	ft_open(t_lst *lst)
{
	t_mtrx_lst	*new_mtrx;
	t_lst_line	*temp;
	int			here_doc[2];
	int			i;

	pipe(here_doc);
	new_mtrx = NULL;
	new_mtrx = ft_read_std(lst);
	ft_expand_m_lst(new_mtrx);
	i = 1;
	temp = new_mtrx->head;
	while (i <= new_mtrx->size)
	{
		ft_putlst_fd(temp->lst, 0 ,here_doc[1]);
		write(here_doc[1], "\n", 1);
		temp = temp->next;
		i++;
	}
	ft_delete_matrix(new_mtrx);
	dup2(here_doc[0], STDIN_FILENO);
	close(here_doc[1]);
	close(here_doc[0]);
}

static t_mtrx_lst	*ft_read_std(t_lst *lst)
{
	t_mtrx_lst	*new_mtrx;
	t_lst		*temp;
	char		*read_line;
	char		*limiter;
	int			size;

	size = ft_strlen(limiter = ft_cpy_lst_to_array(lst));
	new_mtrx = ft_init_matrix();
	while (1)
	{
		write(2, ">> ", 3);
		read_line = get_next_line(STDOUT_FILENO);
		if (ft_strncmp(read_line, limiter, size -1) == 0)
		{
			free(read_line);
			read_line = NULL;
			break ;
		}
		temp = ft_create_lst_add_str(read_line);
		if (temp->last->c == '\n')
			ft_remove_node_back(temp);
		ft_scanner_input(temp);
		ft_add_list_back(new_mtrx, temp);
		free(read_line);
		read_line = NULL;
	}
	free(limiter);
	return (new_mtrx);
}
