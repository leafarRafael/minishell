/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:40:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 16:21:56 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"
#include "minishell.h"

static void	ft_delete(t_ast *tree, t_ast_n *node);

void	ft_delete_tree(t_ast *tree)
{
	if (!tree)
		return ;
	if (tree->root)
		ft_delete(tree, tree->root);
	free(tree);
	tree = NULL;
}

static void	ft_delete(t_ast *tree, t_ast_n *node)
{
	if (node)
	{
		ft_delete(tree, node->left);
		ft_delete(tree, node->right);
		free(node);
		node = NULL;
		tree->size--;
	}
}
