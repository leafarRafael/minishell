/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popule_matrix_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:02:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 08:37:05 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_separate_operators(t_matrix_lst	*matrix_lst, t_lst *input_user)
{
	t_lst	*new_list;
	t_node	*node;
	int		i;

	new_list = ft_init_lst();
	i = 0;
	while (input_user->size > 0)
	{
		if (is_operator(input_user->head->type))
		{
			if (new_list->size != 0)
				ft_add_list_back(matrix_lst, new_list);
			if (i != 0)
				new_list = ft_init_lst();
			if (input_user->head->type == input_user->head->next->type && input_user->head->next != input_user->head)
			{
				node = ft_remove_return_node(input_user, input_user->head);
				ft_addnode_back(new_list, node);
				node = ft_remove_return_node(input_user, input_user->head);
				ft_addnode_back(new_list, node);
			}
			else
			{
				node = ft_remove_return_node(input_user, input_user->head);
				ft_addnode_back(new_list, node);
			}
			ft_add_list_back(matrix_lst, new_list);
			if (input_user->size != 0)
				new_list = ft_init_lst();
		}
		else
		{
			node = ft_remove_return_node(input_user, input_user->head);
			ft_addnode_back(new_list, node);
		}
		i++;
	}
	if (new_list != matrix_lst->last->lst)
		ft_add_list_back(matrix_lst, new_list);
	return (0);
}
