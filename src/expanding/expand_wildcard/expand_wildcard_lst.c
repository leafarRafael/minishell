/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_lst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:53:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/27 12:58:44 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

static int	find_prefix(t_lst *inlst, t_lst *this_lst);
static int	find_sufix(t_lst *inlst, t_lst *this_lst);
static int	find_infix(t_lst *inlst, t_lst *this_lst);
static int	ft_remove_wild_dup(t_lst *inlst, t_lst *this_lst);

void	ft_expand_lst_wildcard(t_lst *lst, t_mlst *dir_content)
{
	t_llst	*current;
	t_llst	*next;
	int		i;

	current = dir_content->head;
	next = current->next;
	i = 1;
	while (i <= dir_content->size)
	{
		if (find_prefix(current->lst, lst))
		{
			ft_rmv_spcfc_lst_mtrx(dir_content, current);
			if (dir_content->size == 0)
				break ;
			i--;
		}
		current = next;
		next = next->next;
		i++;
	}
}

static int	find_prefix(t_lst *inlst, t_lst *this_lst)
{
	t_lst	*inlst_cpy;
	t_lst	*this_cpy;

	if (!inlst || !this_lst)
		return (1);
	if (this_lst->size == 1 && this_lst->head->type == WILDCARD)
		return (0);
	inlst_cpy = ft_duplst(inlst, ft_cpynode, ft_add_node_back);
	this_cpy = ft_duplst(this_lst, ft_cpynode, ft_add_node_back);
	while(this_cpy->head->type != WILDCARD)
	{
		if (inlst_cpy->size == 0)
			return (1);
		if (inlst_cpy->head->c != this_cpy->head->c)
			return (1) ;
		ft_remove_node_front(this_cpy);
		ft_remove_node_front(inlst_cpy);
	}
	return (find_sufix(inlst_cpy, this_cpy));
}

static int	find_sufix(t_lst *inlst, t_lst *this_lst)
{
	if (this_lst->size == 1 && this_lst->last->type == WILDCARD)
		return (lst_rmv_back(this_lst));
	while(this_lst->last->type != WILDCARD)
	{
		if (inlst->size == 0)
			return (1);
		if (inlst->last->c != this_lst->last->c)
			return (1) ;
		lst_rmv_back(this_lst);
		lst_rmv_back(inlst);
	}
	return (find_infix(inlst, this_lst));
}

static int	ft_find_infix_healper(t_lst *inlst, t_lst *this_lst);

static int	find_infix(t_lst *inlst, t_lst *this_lst)
{
	if (this_lst->size == 0)
		return (0);
	if (inlst->size == 0 && this_lst->size != 0)
		return (1);
	if (ft_remove_wild_dup(inlst, this_lst))
		return (ft_delete_list(inlst) + ft_delete_list(this_lst));
	while (inlst->size > 0)
	{
		if (ft_find_infix_healper(inlst, this_lst))
		{
			lst_rmv_back(inlst);
			if (inlst->size == 0)
				return (1);
		}
		else
			return(0);
	}
	return (1);
}

static int	ft_find_infix_healper(t_lst *in, t_lst *this_lst)
{
	t_node	*node;
	t_lst	*cpy_inlst;

	if (this_lst->size == 1 && this_lst->last->c == in->last->c)
		return (0);
	node = this_lst->last;
	cpy_inlst = ft_duplst(in, ft_cpynode, ft_add_node_back);
	while (cpy_inlst->last->c == node->c)
	{
		if (node->c != cpy_inlst->last->c)
			return (ft_delete_list(cpy_inlst) +30);
		lst_rmv_back(cpy_inlst);
		node = node->prev;
		if (node->type == WILDCARD)
		{
			while (this_lst->size)
			{
				lst_rmv_back(this_lst);
				if (this_lst->last->type == WILDCARD)
					break ;
			}
			return (lst_rmv_back(in) + find_infix(in, this_lst) + ft_delete_list(cpy_inlst));
		}
		if (node == this_lst->last)
		{
			while (this_lst->size)
				lst_rmv_back(this_lst);
			return (0);
		}
	}
}

static int ft_remove_wild_dup(t_lst *inlst, t_lst *this_lst)
{
	if (this_lst->last->type == WILDCARD)
		while (this_lst->size > 0)
		{
			if (this_lst->last->type != WILDCARD)
				break ;
			lst_rmv_back(this_lst);
			if (this_lst->size == 0)
				return (1);
		}
	if (this_lst->head->type == WILDCARD)
		while (this_lst->size > 0)
		{
			if (this_lst->head->type != WILDCARD)
				break ;
			ft_remove_node_front(this_lst);
			if (this_lst->size == 0)
				return (1);
		}
	return (0);
}
