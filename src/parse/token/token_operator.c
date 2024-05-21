/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:04:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 09:02:34 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void create_token(t_lst *lst, t_token *v);

void	token_operator(t_lst *lst, t_mlst *matrix)
{
	t_token	variables;

	if (lst->size == 0)
		return ;
	while (lst->head->type == WH_SPACE)
		ft_remove_node_front(lst);
	variables.type = lst->head->type;
	variables.new_lst = ft_init_lst();
	create_token(lst, &variables);
	ft_add_list_back(matrix, variables.new_lst);
}

static void create_token(t_lst *lst, t_token *v)
{
	while (lst->head->type == v->type)
	{
		v->node = ft_remove_return_node(lst, lst->head);
		ft_add_node_back(v->new_lst, v->node);
		if (lst->size == 0)
			break ;
		if (v->type == OPEN_PAREN || v->type == CLOSE_PAREN)
			break ;
	}
}