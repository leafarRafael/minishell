/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:34:11 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 14:31:30 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

static void	ft_add_right(t_ast_n	*node, t_ast_n *new_node);
static int	if_have_node(t_ast *tree, t_mnode *mtrx);

void	ft_tree_add_right(t_ast *tree, t_mnode *matrix)
{
	t_ast_var	v;

	if (!tree)
		return ;
	if (if_have_node(tree, matrix) != 0)
		return ;
	v.ast_node = ft_init_new_ast_node();
	v.ast_node->m_lst = matrix;
	tree->size++;
	if (!tree->root)
		tree->root = v.ast_node;
	else
		ft_add_right(tree->root, v.ast_node);
}

static void	ft_add_right(t_ast_n	*node, t_ast_n *new_node)
{
	if (node->right == NULL)
		node->right = new_node;
	else
		ft_add_right(node->right, new_node);
}


static int	if_have_node(t_ast *tree, t_mnode *mtrx)
{
	t_ast_n *temp;

	if (!tree)
		return (-1);
	if (!tree->root)
		return (0);
	temp = tree->root;
	while (temp != NULL)
	{
		if (temp->m_lst == mtrx)
			return (-1);
		temp = temp->right;
	}
	return (0);
}