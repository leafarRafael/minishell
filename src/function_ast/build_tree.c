/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:29:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/11 18:34:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

void	ft_build_tree(t_ast *tree, t_mtrx_lst *matrix, int value)
{
	t_ast_var	v;

	if (!tree)
		return ;
	if (!matrix)
		return ;
	v.ast_node = ft_init_new_ast_node();
	v.ast_node->m_lst = matrix;
	if (tree->root == NULL)
		tree->root = v.ast_node;
	if (value < tree->root->type && tree->root->right == NULL)
	{
		v.temp = tree->root->left;
		tree->root->left = v.ast_node;
	}
}
