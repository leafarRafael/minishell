/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:31:14 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/10 11:33:36 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "minishell.h"

int	ft_create_fd_here_doc(t_lst *lst)
{
	t_redirect	h_doc;

	h_doc.noting_expand = 0;
	if (lst->head->type == D_QUOTES || lst->head->type == S_QUOTES)
	{
		ft_remove_node_back(lst);
		ft_remove_node_front(lst);
		h_doc.noting_expand++;
	}
	if (h_doc.noting_expand < 0)
		ft_expand_m_lst(h_doc.new_mtrx);
	pipe(h_doc.here_doc);
	h_doc.new_mtrx = NULL;
	h_doc.eof = ft_cpy_lst_to_array(lst);
	h_doc.new_mtrx = ft_read_std(lst, h_doc.eof);
	h_doc.i = 1;
	h_doc.line_in_mlst = h_doc.new_mtrx->head;
	while (h_doc.i <= h_doc.new_mtrx->size)
	{
		ft_putlst_fd(h_doc.line_in_mlst->lst, 0 ,h_doc.here_doc[1]);
		write(h_doc.here_doc[1], "\n", 1);
		h_doc.line_in_mlst = h_doc.line_in_mlst->next;
		h_doc.i++;
	}
	ft_delete_matrix(h_doc.new_mtrx);
	close(h_doc.here_doc[1]);
	return (h_doc.here_doc[0]);
}

t_mlst	*ft_read_std(t_lst *lst, char *eof)
{
	t_redirect	h_doc;

	h_doc.size = ft_strlen(eof);
	h_doc.new_mtrx = ft_init_matrix();
	while (1)
	{
		write(2, ">> ", 3);
		h_doc.read_line = get_next_line(STDOUT_FILENO);
		if (ft_strncmp(h_doc.read_line, eof, h_doc.size -1) == 0)
		{
			free(h_doc.read_line);
			h_doc.read_line = NULL;
			break ;
		}
		h_doc.new_lst = ft_create_lst_add_str(h_doc.read_line);
		if (h_doc.new_lst->last->c == '\n')
			ft_remove_node_back(h_doc.new_lst);
		ft_scanner_simple_operator(h_doc.new_lst);
		ft_add_list_back(h_doc.new_mtrx, h_doc.new_lst);
		free(h_doc.read_line);
		h_doc.read_line = NULL;
	}
	free(eof);
	return (h_doc.new_mtrx);
}
