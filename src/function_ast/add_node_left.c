/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:17:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:51:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

static void	ft_add_left(t_ast_n	*node, t_ast_n *new_node);
static int	if_have_node(t_ast *tree, t_mnode *mtrx);

void	ft_tree_add_left(t_ast *tree, t_mnode *matrix)
{
	t_ast_var	v;

	if (!tree)
		return ;
	if (if_have_node(tree, matrix) != 0)
		return ;
	matrix->in_tree = 0;
	v.ast_node = ft_init_new_ast_node();
	v.ast_node->m_lst = matrix;
	tree->size++;
	if (!tree->root)
		tree->root = v.ast_node;
	else
		ft_add_left(tree->root, v.ast_node);
}

static void	ft_add_left(t_ast_n	*node, t_ast_n *new_node)
{
	if (node->left == NULL)
		node->left = new_node;
	else
		ft_add_left(node->left, new_node);
}

static int	if_have_node(t_ast *tree, t_mnode *mtrx)
{
	t_ast_n	*temp;

	if (!tree)
		return (-1);
	if (!tree->root)
		return (0);
	temp = tree->root;
	while (temp != NULL)
	{
		if (temp->m_lst == mtrx)
			return (-1);
		temp = temp->left;
	}
	return (0);
}
