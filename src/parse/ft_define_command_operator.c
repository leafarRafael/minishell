/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_command_operator.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:06:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/11 12:56:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_define_cmd_operator(t_mtrx_mtrx *m_m_lst)
{
	int		i;
	t_mnode	*temp;

	if (!m_m_lst)
		return (-1);
	if (m_m_lst->size == 0)
		return (-1);
	temp = m_m_lst->head;
	i = 1;
	while (i <= m_m_lst->size)
	{
		temp->type = temp->matrix->head->lst->head->priority;
		temp = temp->next;
		i++;
	}
	return (0);
}
