/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_m_lst_to_cmtrx.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:18:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 13:35:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

static int	ft_expande_before_copie(t_mlst *lst_matrix);

char	**ft_expand_m_lst_to_cmtrx(t_mlst *lst_matrix)
{
	t_var_matrix	v;

	if (!lst_matrix)
		return (v.matrix);
	v.matrix = ft_calloc(sizeof(char *), lst_matrix->size + 1);
	v.current_lst = lst_matrix->head;
	v.index = 0;
	v.i = 1;
	while (v.i <= lst_matrix->size)
	{
		ft_expander_lst_token(v.current_lst->lst);
		if (v.current_lst->lst->size != 0)
		{
			v.matrix[v.index] = ft_cpy_lst_to_array(v.current_lst->lst);
			v.index++;
		}
		v.current_lst = v.current_lst->next;
		v.i++;
	}
	return (v.matrix);
}

static int	ft_expande_before_copie(t_mlst *lst_matrix)
{
	t_var_matrix	v;
	int				size;

	v.current_lst = lst_matrix->head;
	size = lst_matrix->size;
	v.i = 1;
	while (v.i <= size)
	{
		ft_expander_lst_token(v.current_lst->lst);
		if (v.current_lst->lst->size == 0)
		{
			ft_rmv_spcfc_lst_mtrx(lst_matrix, v.current_lst);
			if (lst_matrix->size == 0)
				return (-1);
			v.current_lst = lst_matrix->head;
			size = lst_matrix->size;
			v.i = 1;
		}
		else
		{
			v.current_lst = v.current_lst->next;
			v.i++;
		}
	}
	return (0);
}
