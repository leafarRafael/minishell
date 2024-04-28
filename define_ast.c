/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:39 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/28 09:55:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_populetree(t_ast *tree, t_mtrx_mtrx *mtrx_mtrx)
{
	t_mnode		*temp;
	int			i;
	int			type;

	i = 1;
	temp = mtrx_mtrx->last;
	type = temp->type;
	while (i <= mtrx_mtrx->size)
	{
		if (!is_operator(type))
			ft_tree_add_left(tree, temp);
		temp = temp->prev;
		type = temp->type;
		i++;
	}
}