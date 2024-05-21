/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_mtrx_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:40:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 09:29:38 by rbutzke          ###   ########.fr       */
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
	v.index = 0;
	v.i = 1;
	while (v.i <= mlst->size)
	{
		ft_expander_lst_token(v.current_lst->lst);
		v.current_lst = v.current_lst->next;
		v.i++;
	}
}
