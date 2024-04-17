/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_priority_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:01:19 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/17 13:03:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_define_priority_operator(t_mtrx_mtrx *m_m_lst)
{
	t_var_m_mlst	v;

	v.i = 1;
	v.current = m_m_lst->head;
	while (v.i <= m_m_lst->size)
	{

		v.current = v.current->next;
		v.i++;
	}

}