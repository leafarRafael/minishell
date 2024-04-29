/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popule_matrix_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:02:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 16:29:24 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_matrix_op(t_lst *n_lst, t_mtrx_lst *m_lst, t_lst *input, int i);

int	ft_separate_operators(t_mtrx_lst *matrix_lst, t_lst *input_user)
{
	t_lst	*new_list;
	t_node	*node;
	int		i;

	new_list = ft_init_lst();
	i = 0;
	while (input_user->size > 0)
	{
		if (is_operator(input_user->head->type))
			ft_matrix_op(new_list, matrix_lst, input_user, i);
		else
		{
			node = ft_remove_return_node(input_user, input_user->head);
			ft_add_node_back(new_list, node);
		}
		i++;
	}
	if (new_list != matrix_lst->last->lst)
		ft_add_list_back(matrix_lst, new_list);
	return (0);
}

static void	ft_matrix_op(t_lst *n_lst, t_mtrx_lst *m_lst, t_lst *input, int i)
{
	t_node	*node;

	if (n_lst->size != 0)
		ft_add_list_back(m_lst, n_lst);
	if (i != 0)
		n_lst = ft_init_lst();
	if (input->head->type == input->head->next->type
		&& input->head->next != input->head)
	{
		node = ft_remove_return_node(input, input->head);
		ft_add_node_back(n_lst, node);
		node = ft_remove_return_node(input, input->head);
		ft_add_node_back(n_lst, node);
	}
	else
	{
		node = ft_remove_return_node(input, input->head);
		ft_add_node_back(n_lst, node);
	}
	ft_add_list_back(m_lst, n_lst);
	if (input->size != 0)
		n_lst = ft_init_lst();
}
