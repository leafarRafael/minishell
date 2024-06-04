/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:59:14 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:56:05 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	create_token(t_lst *lst, t_token *v);

void	token_command(t_lst *lst, t_mlst *matrix)
{
	t_token	varibles;

	if (lst->size == 0)
		return ;
	while (lst->head->type == WH_SPACE)
		ft_remove_node_front(lst);
	if (is_operator(lst->head->type))
		return ;
	varibles.new_lst = ft_init_lst();
	create_token(lst, &varibles);
	ft_add_list_back(matrix, varibles.new_lst);
	token_command(lst, matrix);
}

static void	create_token(t_lst *lst, t_token *v)
{
	while (!is_operator(lst->head->type) && lst->head->type != WH_SPACE)
	{
		if (is_operator_redirect(lst->head->type))
		{
			if (v->new_lst->size > 0)
				break ;
			while (is_operator_redirect(lst->head->type))
			{
				v->node = ft_remove_return_node(lst, lst->head);
				ft_add_node_back(v->new_lst, v->node);
			}
			break ;
		}
		v->node = ft_remove_return_node(lst, lst->head);
		ft_add_node_back(v->new_lst, v->node);
		if (lst->size == 0)
			break ;
	}
}
