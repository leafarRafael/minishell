/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:39 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/17 18:23:35 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_populetree(t_ast *tree, t_mtrx_mtrx *mtrx_mtrx)
{
	t_mnode		*temp;
	int			i;
	int			type;

	i = 1;
	temp = mtrx_mtrx->head;
	type = temp->type;
	while (i <= mtrx_mtrx->size)
	{
		if (is_operator(type))
			ft_build_tree(tree, temp, type);
		temp = temp->next;
		type = temp->type;
		i++;
	}
	ft_printtree(tree->root, mtrx_mtrx);
}

static t_mnode	*ft_find_less_priority(t_mtrx_mtrx *mtrx_mtrx)
{
	t_var_m_mlst	v;

	v.i = 1;
	v.current = mtrx_mtrx->head;
	while (v.i < mtrx_mtrx->size)
	{
		v.current = v.current->next;
		v.i++;
	}
	return (v.current);
}