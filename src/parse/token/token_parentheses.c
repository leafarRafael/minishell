/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:07:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:56:48 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	create_token(t_lst *lst, t_token *v);
static void	valid_add_redirect(t_lst *lst, t_token *v);

void	token_parent(t_lst *lst, t_mlst *matrix)
{
	t_token	variables;

	if (!lst)
		return ;
	if (lst->size == 0)
		return ;
	variables.new_lst = ft_init_lst();
	create_token(lst, &variables);
	valid_add_redirect(lst, &variables);
	ft_add_list_back(matrix, variables.new_lst);
}

static void	create_token(t_lst *lst, t_token *v)
{
	int		parent;

	parent = lst->head->paren;
	v->node = ft_remove_return_node(lst, lst->head);
	ft_add_node_back(v->new_lst, v->node);
	while (lst->head->paren != parent)
	{
		v->node = ft_remove_return_node(lst, lst->head);
		ft_add_node_back(v->new_lst, v->node);
		if (lst->head->paren == parent)
		{
			v->node = ft_remove_return_node(lst, lst->head);
			ft_add_node_back(v->new_lst, v->node);
			break ;
		}
		if (lst->size == 0)
			break ;
	}
}

static void	valid_add_redirect(t_lst *lst, t_token *v)
{
	if (lst->size != 0)
	{
		while (!is_operator(lst->head->type))
		{
			v->node = ft_remove_return_node(lst, lst->head);
			ft_add_node_back(v->new_lst, v->node);
			if (lst->size == 0)
				break ;
		}
	}
}
