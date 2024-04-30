/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_command_operator.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:06:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/30 11:29:42 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_cmd_opertor(t_mtrx_mtrx *m_m_lst);
static void	ft_remove_rdrct(t_mtrx_mtrx *m_m_lst);

int	ft_remove_cmd_status(t_mtrx_mtrx *m_m_lst)
{
	if (!m_m_lst)
		return (-1);
	if (m_m_lst->size == 0)
		return (-1);
	ft_remove_rdrct(m_m_lst);
	return (0);
}

// TODO
static void	ft_remove_cmd_opertor(t_mtrx_mtrx *m_m_lst)
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

static void	ft_remove_rdrct(t_mtrx_mtrx *m_m_lst)
{
	int			count[2];
	int			size;
	t_mnode		*mnoode_temp;
	t_lst_line	*lst_temp;
	t_lst_line	*lst_next;

	mnoode_temp = m_m_lst->head;
	count[0] = 1;
	size = mnoode_temp->matrix->size;
	while (count[0] <= m_m_lst->size)
	{
		lst_temp = mnoode_temp->matrix->head;
		lst_next = lst_temp->next;
		count[1] = 1;
		while (count[1] <= size)
		{
			if (lst_temp->lst->head->type
				& (REDI_IN | HERE_DOC | REDI_OUT | APPEND))
			{
				ft_print_array_lst(lst_temp->lst, 0);
				ft_rmv_spcfc_lst_mtrx(mnoode_temp->matrix, lst_temp);

			}
			lst_temp = lst_next;
			lst_next = lst_next->next;
			count[1]++;
		}
		mnoode_temp = mnoode_temp->next;
		count[0]++;
	}
}
