/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_lst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:53:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/26 17:09:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

static int	find_prefix(t_lst *inlst, t_lst *this_lst);
static int	find_sufix(t_lst *inlst, t_lst *this_lst);
static int	find_infix(t_lst *inlst, t_lst *this_lst);
static int	ft_remove_dup(t_lst *lst);

void	ft_expand_lst_wildcard(t_lst *lst, t_mlst *dir_content)
{
	t_llst	*current;
	t_llst	*next;
	t_lst	*cpy;
	int		i;

	current = dir_content->head;
	next = current->next;
	i = 1;
	while (i <= dir_content->size)
	{
		cpy = ft_duplst(lst, ft_cpynode, ft_add_node_back);
		if (find_prefix(current->lst, cpy))
		{
			ft_rmv_spcfc_lst_mtrx(dir_content, current);
			i--;
		}
		ft_delete_list(cpy);
		cpy = NULL;
		if (dir_content->size == 0)
			break ;
		current = next;
		next = next->next;
		i++;
	}
}

static int	find_prefix(t_lst *inlst, t_lst *this_lst)
{
	t_lst	*cpy;

	if (!inlst || !this_lst)
		return (1);
	if (this_lst->size == 1 && this_lst->head->type == WILDCARD)
		return (ft_remove_node_front(this_lst));
	cpy = ft_duplst(inlst, ft_cpynode, ft_add_node_back);
	while(this_lst->head->type != WILDCARD)
	{
		if (cpy->head->c != this_lst->head->c)
			return (1);
		ft_remove_node_front(this_lst);
		ft_remove_node_front(cpy);
		if (this_lst->size == 0)
			return (1);
		if (cpy->size == 0)
			return (1);
	}
	return (find_sufix(cpy, this_lst));
}

static int	find_sufix(t_lst *inlst, t_lst *this_lst)
{
	if (!inlst || !this_lst)
		return (1);
	if (this_lst->size == 1 && this_lst->last->type == WILDCARD)
		return (ft_remove_node_back(this_lst));
	while(this_lst->last->type != WILDCARD)
	{
		if (inlst->last->c != this_lst->last->c)
			return (1);
		ft_remove_node_back(this_lst);
		ft_remove_node_back(inlst);
		if (this_lst->size == 0)
			return (0);
		if (inlst->size == 0)
			return (1);
	}
	return (find_infix(inlst, this_lst));
}

int	compare(t_lst *inlst, t_lst *this_lst);

static int	find_infix(t_lst *inlst, t_lst *this_lst)
{
	if (!inlst || !this_lst)
		return (1);
	if (this_lst->size == 0)
		return (ft_delete_list(this_lst), ft_delete_list(inlst));
	if (this_lst->size == 1 && this_lst->last->type == WILDCARD)
		return (ft_remove_node_back(this_lst));
	if (ft_remove_dup(this_lst))
		return (1);
/* 	while (inlst->size > 0)
	{
		if (compare(inlst, this_lst))
			ft_remove_node_back(inlst);
		else
			return (0);
	} */
	return (0);
}

int	compare(t_lst *inlst, t_lst *this_lst)
{
	t_lst	*in_cpy;
	t_lst	*this_cpy;

/* 	if (this_lst->size == 1 && inlst->last->c != this_lst->last->c)
		return (1); */
	in_cpy = ft_duplst(inlst, ft_cpynode, ft_add_node_back);
	this_cpy = ft_duplst(this_lst, ft_cpynode, ft_add_node_back);
	while (1)
	{
		ft_putlst_fd(this_cpy, 1, 2);
		ft_putlst_fd(in_cpy, 1, 2);
		if (in_cpy->last->c != this_cpy->last->c)
		{
			ft_delete_list(in_cpy);
			ft_delete_list(this_cpy);
			return (1);
		}
		else
		{
			ft_remove_node_back(in_cpy);
			ft_remove_node_back(this_cpy);
		}
		if (this_lst->size == 0)
			return (1);
		if (in_cpy->size == 0)
			return (0);
	}
	return (0);
}

static int	ft_remove_dup(t_lst *lst)
{
	while (lst->head->type == WILDCARD)
		ft_remove_node_front(lst);
	if (lst->size == 0)
		return (1);
	while (lst->last->type == WILDCARD)
		ft_remove_node_back(lst);
	if (lst->size == 0)
		return (1);
	return (0);
}
