/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_command_operator.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:06:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 09:40:14 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

static void	ft_remove_cmd_opertor(t_mmlst *m_m_lst);
static void	ft_remove_rdrct(t_mmlst *m_m_lst);

int	ft_remove_cmd_status(t_mmlst *m_m_lst)
{
	if (!m_m_lst)
		return (-1);
	if (m_m_lst->size == 0)
		return (-1);
	ft_remove_rdrct(m_m_lst);
	return (0);
}

static void	ft_remove_cmd_opertor(t_mmlst *m_m_lst)
{
	int		i;
	t_mnode	*temp;

	temp = m_m_lst->head;
	i = 1;
	while (i <= m_m_lst->size)
	{
		temp->type = temp->matrix->head->lst->head->type;
		temp = temp->next;
		i++;
	}
}

static void	ft_remove_rdrct(t_mmlst *m_m_lst)
{
	t_add_token	v;

	v.mnoode_temp = m_m_lst->head;
	v.count_i = 1;
	while (v.count_i <= m_m_lst->size)
	{
		v.lst_temp = v.mnoode_temp->matrix->head;
		v.lst_next = v.lst_temp->next;
		v.count_x = 1;
		v.size = v.mnoode_temp->matrix->size;
		while (v.count_x <= v.size)
		{
			if (v.lst_temp->lst->head->type
				& (REDI_IN | HERE_DOC | REDI_OUT | APPEND))
				ft_rmv_spcfc_lst_mtrx(v.mnoode_temp->matrix, v.lst_temp);
			v.lst_temp = v.lst_next;
			v.lst_next = v.lst_next->next;
			v.count_x++;
		}
		v.mnoode_temp = v.mnoode_temp->next;
		v.count_i++;
	}
}
