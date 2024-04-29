/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:59:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:11:31 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "scanner.h"
#include <stdio.h>

static int		find_variable(t_lst *lst, t_lst *lst_temp);
static void		ft_remove_node_var(t_lst *lst, t_lst *temp);
static void		ft_replace_lst(t_lst *lst, t_lst *temp, char *env);
static t_node	*ft_line_less(t_node *node, int *i);

int	ft_expander_lst_token(t_lst *lst)
{
	t_expand	v;

	v.lst_temp.size = 0;
	if (!lst || lst->size == 0)
		return (-1);
	if (lst->size == 1)
		return (-1);
	if (find_variable(lst, &v.lst_temp))
		return (-1);
	v.array_var = ft_cpy_lst_to_array(&v.lst_temp);
	v.env = getenv(&v.array_var[1]);
	free(v.array_var);
	if (v.env)
	{
		ft_replace_lst(lst, &v.lst_temp, v.env);
		ft_expander_lst_token(lst);
	}
	else
	{
		ft_remove_node_var(lst, &v.lst_temp);
		ft_expander_lst_token(lst);
	}
	return (0);
}

static int	find_variable(t_lst *lst, t_lst *lst_temp)
{
	t_expand	v;

	v.i = 1;
	v.node = lst->head;
	while (v.i <= lst->size)
	{
		if (v.node->type == DOLLAR)
		{
			v.node->type = NO_OP_TYPE;
			lst_temp->head = v.node;
			lst_temp->last = v.node;
			lst_temp->size++;
			v.node = ft_line_less(v.node, &v.i);
			while (v.node->type == NO_OP_TYPE && v.i <= lst->size)
			{
				lst_temp->size++;
				lst_temp->last = v.node;
				v.node = ft_line_less(v.node, &v.i);
			}
			return (0);
		}
		v.node = ft_line_less(v.node, &v.i);
	}
	return (-1);
}

static void	ft_remove_node_var(t_lst *lst, t_lst *temp)
{
	t_expand	v;

	if (temp->head == temp->last && temp->size == 1)
		return ;
	v.node = temp->head;
	v.next_node = v.node->next;
	while (temp->size > 0)
	{
		ft_remove_specific_node(lst, v.node);
		temp->size--;
		if (temp->size == 0)
			break ;
		v.node = v.next_node;
		v.next_node = v.node->next;
	}
}

static void	ft_replace_lst(t_lst *lst, t_lst *temp, char *env)
{
	t_expand	v;

	v.is_head = 0;
	v.is_last = 0;
	v.node = temp->head;
	v.next_node = v.node->next;
	v.prev_head = temp->head->prev;
	v.next_last = temp->last->next;
	if (temp->head == lst->head)
		v.is_head++;
	if (temp->last == lst->last)
		v.is_last++;
	ft_remove_node_var(lst, temp);
	v.poin_lst = ft_init_lst();
	ft_add_string_in_list(v.poin_lst, env);
	ft_scanner_add_literal(v.poin_lst);
	ft_lst_btwn_lst(lst, v.prev_head, v.next_last, v.poin_lst);
	if (v.is_head > 0)
		lst->head = v.poin_lst->head;
	if (v.is_last > 0)
		lst->last = v.poin_lst->last;
	free(v.poin_lst);
}

static t_node	*ft_line_less(t_node *node, int *i)
{
	node = node->next;
	(*i)++;
	return (node);
}
