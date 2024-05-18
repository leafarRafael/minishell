/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:39 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/17 13:19:22 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_define_ast(t_ast *tree, t_mmlst *mmlst)
{
	t_mnode *temp;
	int i;
	int type;

	i = 1;
	temp = mmlst->last;
	type = temp->type;
	while (i <= mmlst->size)
	{
		if (!is_operator(type))
		{
			if (temp->in_tree == -42)
				ft_tree_add_left(tree, temp);
		}
		temp = temp->prev;
		type = temp->type;
		i++;
	}
}
