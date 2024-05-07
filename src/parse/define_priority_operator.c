/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_priority_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:01:19 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 07:58:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_valid_op_in_subshell(t_mmlst *m_m_lst)
{
	t_var_m_mlst	v;

	v.i = 1;
	v.current = m_m_lst->head;
	while (v.i <= m_m_lst->size)
	{
		if (v.current->type == OPEN_PAREN || v.current->type == CLOSE_PAREN)
			v.current->in_parent = v.current->matrix->head->lst->head->paren;
		else
			v.current->in_parent = -42;
		v.current = v.current->next;
		v.i++;
	}
}
