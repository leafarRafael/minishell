/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:59:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 09:42:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

static int		find_variable(t_lst *lst, t_lst *lst_temp);
static void		ft_remove_node_var(t_lst *lst, t_lst *temp);
static void		ft_replace_lst(t_lst *lst, t_lst *temp, char *env);
static int		ft_status(t_lst *lst, t_node *node);

int	ft_expander_lst_token(t_lst *lst)
{
	t_expand	v;

	v.lst_temp.size = 0;
	if (find_variable(lst, &v.lst_temp))
		return (-1);
	if (ft_status(lst, v.lst_temp.head))
	{
		ft_expander_lst_token(lst);
		return (0);
	}
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
	lst_temp->head = find_type_rtrn_ptr(lst, DOLLAR);
	if (!lst_temp->head)
		return (-1);
	lst_temp->head->type = NO_OP_TYPE;
	lst_temp->size++;
	lst_temp->last = lst_temp->head;
	v.node = lst_temp->head->next;
	if (v.node == lst_temp->head)
		return (-1);
	while (v.node->type == NO_OP_TYPE && v.node != lst->head)
	{
		lst_temp->size++;
		lst_temp->last = v.node;
		v.node = v.node->next;
	}
	return (0);
}

static void	ft_remove_node_var(t_lst *lst, t_lst *temp)
{
	t_node	*node;
	t_node	*next;

	if (temp->head == temp->last && temp->size == 1)
		return ;
	node = temp->head;
	next = node->next;
	while (temp->size > 0)
	{
		ft_remove_specific_node(lst, node);
		temp->size--;
		if (temp->size == 0)
			break ;
		node = next;
		next = node->next;
	}
}

static void	ft_replace_lst(t_lst *lst, t_lst *temp, char *env)
{
	t_expand	v;

	v.poin_lst = ft_init_lst();
	ft_add_string_in_list(v.poin_lst, env);
	ft_scanner_after_expand(v.poin_lst);
	insert_node_between(lst, temp->last, v.poin_lst);
	ft_remove_node_var(lst, temp);
	free(v.poin_lst);
}

static int	ft_status(t_lst *lst, t_node *node)
{
	char	*status;
	t_lst	*temp;

	if (node->next->c != '?')
		return (0);
	node->type = META_LITERAL;
	temp = ft_init_lst();
	status = ft_itoa(g_status_child);
	ft_add_string_in_list(temp, status);
	ft_scanner_after_expand(temp);
	insert_node_between(lst, node->next, temp);
	ft_remove_specific_node(lst, node->next);
	ft_remove_specific_node(lst, node);
	free(status);
	free(temp);
	return (1);
}
