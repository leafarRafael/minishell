/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_create_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:55:21 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 09:25:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static t_node	*ft_find_end_hdoc(t_lst *lst, t_node *start_ptr);
static void		ft_rnd_valid_expand(t_lst *lst,
					t_node *start, t_node *end, t_lst *eof);

void	ft_finished_hdoc(t_lst *lst, t_node *nd, int *hdoc_ctrlname)
{
	t_hdoc	v;

	v.lst_eof = ft_init_lst();
	v.end_hdoc = ft_find_end_hdoc(lst, nd);
	v.is_head = 0;
	v.is_last = 0;
	if (nd == lst->head)
		v.is_head++;
	if (v.end_hdoc == lst->last)
		v.is_last++;
	v.next = v.end_hdoc->next;
	v.prev = nd->prev;
	v.here_doc = ft_initialize_hdoc_lst(hdoc_ctrlname);
	ft_rnd_valid_expand(lst, nd, v.end_hdoc, v.lst_eof);
	ft_write_here_doc(v.here_doc, v.lst_eof);
	ft_lst_btwn_lst(lst, v.prev, v.next, v.here_doc);
	if (v.is_head > 0)
		lst->head = v.here_doc->head;
	if (v.is_last > 0)
		lst->last = v.here_doc->last;
	free(v.here_doc);
}

static void	ft_rnd_valid_expand(t_lst *lst,
			t_node *start, t_node *end, t_lst *eof)
{
	t_node	*next_node;

	next_node = start->next;
	while (start != end)
	{
		ft_add_node_back(eof, ft_cpynode(start));
		ft_remove_specific_node(lst, start);
		start = next_node;
		next_node = next_node->next;
	}
	ft_add_node_back(eof, ft_cpynode(start));
	ft_remove_specific_node(lst, start);
	while (eof->head->c == '<')
		ft_remove_node_front(eof);
	while (eof->head->c == ' ')
		ft_remove_node_front(eof);
}

static t_node	*ft_find_end_hdoc(t_lst *lst, t_node *start_ptr)
{
	t_node	*end_here_doc;

	end_here_doc = start_ptr;
	while (end_here_doc->type == HERE_DOC)
	{
		end_here_doc->type = NO_OP_TYPE;
		end_here_doc = end_here_doc->next;
	}
	while (end_here_doc->type == WH_SPACE)
		end_here_doc = end_here_doc->next;
	while (!ft_hdoc_limiter(end_here_doc->type) && end_here_doc != lst->head)
		end_here_doc = end_here_doc->next;
	return (end_here_doc->prev);
}
