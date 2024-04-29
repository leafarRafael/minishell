/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:17:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:43:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

static void	ft_add_left(t_ast_node	*node, t_ast_node *new_node);

void	ft_tree_add_left(t_ast *tree, t_mnode *matrix)
{
	t_ast_var	v;

	if (!tree)
		return ;
	v.ast_node = ft_init_new_ast_node();
	v.ast_node->m_lst = matrix;
	tree->size++;
	if (!tree->root)
		tree->root = v.ast_node;
	else
		ft_add_left(tree->root, v.ast_node);
}

static void	ft_add_left(t_ast_node	*node, t_ast_node *new_node)
{
	if (node->left == NULL)
		node->left = new_node;
	else
		ft_add_left(node->left, new_node);
}
