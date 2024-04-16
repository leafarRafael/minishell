/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:40:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/16 14:55:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

static void	ft_delete(t_ast *tree, t_ast_node *node);

void	ft_delete_tree(t_ast *tree)
{
	t_ast_node *node;

	if (!tree)
		return ;
	if (tree->root)
		ft_delete(tree, tree->root);
	free(tree);
}

static void ft_delete(t_ast *tree, t_ast_node *node)
{
	if (node);
	{
		if (node->left)
			ft_delete(tree, node->left);
		if (node->right)
			ft_delete(tree, node->right);
		free(node);
		node = NULL;
		tree->root--;
	}
}
