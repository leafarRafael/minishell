/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_command_operator.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:06:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/13 07:05:11 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_define_cmd_opertor(t_mmlst *m_m_lst);
static void	ft_define_infile(t_mmlst *m_m_lst);
static void	ft_define_outfile(t_mmlst *m_m_lst);
static void	add_atribute(t_llst *llst, int type);

int	ft_define_cmd_status(t_mmlst *m_m_lst)
{
	if (!m_m_lst)
		return (-1);
	if (m_m_lst->size == 0)
		return (-1);
	ft_define_cmd_opertor(m_m_lst);
	ft_define_infile(m_m_lst);
	ft_define_outfile(m_m_lst);
	return (0);
}

static void	ft_define_cmd_opertor(t_mmlst *m_m_lst)
{
	int		i;
	t_mnode	*temp;

	temp = m_m_lst->head;
	if (temp->matrix->size == 0)
		return ;
	i = 1;
	while (i <= m_m_lst->size)
	{
		temp->type = temp->matrix->head->lst->head->type;
		temp = temp->next;
		i++;
	}
}

static void	ft_define_infile(t_mmlst *m_m_lst)
{
	int		count[2];
	t_mnode	*mnoode_temp;
	t_llst	*lst_temp;

	mnoode_temp = m_m_lst->head;
	count[0] = 1;
	while (count[0] <= m_m_lst->size)
	{
		lst_temp = mnoode_temp->matrix->head->next;
		count[1] = 1;
		while (count[1] <= mnoode_temp->matrix->size)
		{
			if (lst_temp->prev->lst->head->type == REDI_IN)
				add_atribute(lst_temp, REDI_IN);
			else if (lst_temp->prev->lst->head->type == HERE_DOC)
				lst_temp->rdrct = HERE_DOC;
			lst_temp = lst_temp->next;
			count[1]++;
		}
		mnoode_temp = mnoode_temp->next;
		count[0]++;
	}
}

static void	ft_define_outfile(t_mmlst *m_m_lst)
{
	int		count[2];
	t_mnode	*mnoode_temp;
	t_llst	*lst_temp;

	mnoode_temp = m_m_lst->head;
	count[0] = 1;
	while (count[0] <= m_m_lst->size)
	{
		lst_temp = mnoode_temp->matrix->head;
		count[1] = 1;
		while (count[1] <= mnoode_temp->matrix->size)
		{
			if (lst_temp->prev->lst->head->type == REDI_OUT)
				add_atribute(lst_temp, REDI_OUT);
			else if (lst_temp->prev->lst->head->type == APPEND)
				add_atribute(lst_temp, APPEND);
			lst_temp = lst_temp->next;
			count[1]++;
		}
		mnoode_temp = mnoode_temp->next;
		count[0]++;
	}
}

static void	add_atribute(t_llst *llst, int type)
{
	t_lst	*cpy;

	if (llst->lst->head->type == DOLLAR)
	{
		cpy = ft_duplst(llst->lst, ft_cpynode, ft_add_node_back);
		ft_expander_lst_token(llst->lst);
		if (llst->lst->size == 0)
		{
			cpy->head->type = META_LITERAL;
			ft_delete_list(llst->lst);
			llst->lst = cpy;
		}
		else
			ft_delete_list(cpy);
	}
	llst->rdrct = type;
}
