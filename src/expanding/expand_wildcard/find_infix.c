/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:21 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 09:15:16 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

static int	is_wildcard_content(t_lst *this, t_lst *in, t_lst *cpyin);
static int	is_last_content(t_lst *this, t_lst *in, t_lst *cpyin);
static int	ft_remove_wild_dup(t_lst *inlst, t_lst *this_lst);
static int	ft_find_infix_healper(t_lst *in, t_lst *this);

int	find_infix(t_lst *inlst, t_lst *this_lst)
{
	if (this_lst->size == 0)
		return (ft_delete_list(inlst) + ft_delete_list(this_lst));
	if (inlst->size == 0 && this_lst->size != 0)
		return (ft_delete_list(inlst) + ft_delete_list(this_lst) + 1);
	if (ft_remove_wild_dup(inlst, this_lst))
		return (ft_delete_list(inlst) + ft_delete_list(this_lst));
	while (inlst->size > 0)
	{
		if (ft_find_infix_healper(inlst, this_lst))
		{
			lst_rmv_back(inlst);
			if (inlst->size == 0)
				return (ft_delete_list(inlst) + ft_delete_list(this_lst) + 1);
		}
		else
			return (ft_delete_list(inlst) + ft_delete_list(this_lst));
	}
	return (ft_delete_list(inlst) + ft_delete_list(this_lst) + 1);
}

static int	ft_find_infix_healper(t_lst *in, t_lst *this)
{
	t_node	*node;
	t_lst	*cpyin;

	if (this->size == 1 && this->last->c == in->last->c)
		return (0);
	node = this->last;
	cpyin = ft_duplst(in, ft_cpynode, ft_add_node_back);
	while (cpyin->last->c == node->c)
	{
		lst_rmv_back(cpyin);
		node = node->prev;
		if (node->type == WILDCARD)
			return (is_wildcard_content(this, in, cpyin));
		if (node->prev == this->last && cpyin->last->c == node->c)
			return (is_last_content(this, in, cpyin));
		if (node->c != cpyin->last->c)
			return (ft_delete_list(cpyin) + 30);
		if (cpyin->size == 0)
			return (ft_delete_list(cpyin) + 30);
	}
	return (ft_delete_list(cpyin) + 11);
}

static int	is_wildcard_content(t_lst *this, t_lst *in, t_lst *cpyin)
{
	while (this->size)
	{
		lst_rmv_back(this);
		if (this->last->type == WILDCARD)
			break ;
	}
	return (lst_rmv_back(in) + find_infix(in, this) + ft_delete_list(cpyin));
}

static int	is_last_content(t_lst *this, t_lst *in, t_lst *cpyin)
{
	while (this->size)
		lst_rmv_back(this);
	lst_rmv_back(in);
	ft_delete_list(cpyin);
	return (0);
}

static int	ft_remove_wild_dup(t_lst *inlst, t_lst *this_lst)
{
	while (this_lst->size > 0)
	{
		if (this_lst->last->type != WILDCARD)
			break ;
		lst_rmv_back(this_lst);
		if (this_lst->size == 0)
			break ;
	}
	while (this_lst->size > 0)
	{
		if (this_lst->head->type != WILDCARD)
			break ;
		ft_remove_node_front(this_lst);
		if (this_lst->size == 0)
			break ;
	}
	if (this_lst->size == 0)
		return (1);
	return (0);
}
