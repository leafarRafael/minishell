/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_mtrx_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:40:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/01 11:08:19 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

void	ft_expand_m_lst(t_mtrx_lst *lst_matrix)
{
	t_var_matrix	v;

	if (!lst_matrix)
		return ;
	v.current_lst = lst_matrix->head;
	v.index = 0;
	v.i = 1;
	while (v.i <= lst_matrix->size)
	{
		ft_expander_lst_token(v.current_lst->lst);
		v.current_lst = v.current_lst->next;
		v.i++;
	}
}

void	ft_remove_quote_m_lst(t_mtrx_lst *lst_matrix)
{
	t_var_matrix	v;
	t_node			*node;
	t_node			*next;
	int				x;

	if (!lst_matrix)
		return ;
	v.current_lst = lst_matrix->head;
	v.index = 0;
	v.i = 1;
	while (v.i <= lst_matrix->size)
	{
		node = v.current_lst->lst->head;
		next = node->next;
		x = 1;
		while(x <= v.current_lst->lst->size)
		{
			if (node->type &(D_QUOTES | S_QUOTES))
			{
				ft_remove_specific_node(v.current_lst->lst, node);
				x--;
			}
			node = next;
			next = next->next;
			x++;
		}
		v.current_lst = v.current_lst->next;
		v.i++;
	}
}