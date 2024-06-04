/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_mtrx_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:40:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 15:46:36 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

void	ft_expand_m_lst(t_mlst *mlst)
{
	t_var_matrix	v;

	if (!mlst)
		return ;
	v.current_lst = mlst->head;
	v.next_lst = v.current_lst->next;
	v.i = 1;
	while (v.i <= mlst->size)
	{
		if (find_type_rtrn_ptr(v.current_lst->lst, DOLLAR) != NULL)
		{
			ft_expander_lst_token(v.current_lst->lst);
			if (v.current_lst->lst->size != 0)
				token_after_expand(mlst, v.current_lst);
			v.current_lst = mlst->head;
			v.next_lst = v.current_lst->next;
			v.i = 1;
		}
		if (mlst->size == 0)
			break ;
		v.current_lst = v.next_lst;
		v.next_lst = v.next_lst->next;
		v.i++;
	}
}

void	ft_expand_m_lst_heredoc(t_mlst *mlst)
{
	t_var_matrix	v;

	if (!mlst)
		return ;
	if (mlst->size == 0)
		return ;
	v.current_lst = mlst->head;
	v.next_lst = v.current_lst->next;
	v.i = 1;
	while (v.i <= mlst->size)
	{
		ft_expander_lst_token(v.current_lst->lst);
		if (mlst->size == 0)
			break ;
		v.current_lst = v.next_lst;
		v.next_lst = v.next_lst->next;
		v.i++;
	}
}
