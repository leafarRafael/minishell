/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:40:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/30 14:01:22 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"
#include "minishell.h"

static void	ft_delete(t_ast *tree, t_ast_n *node);

void	ft_delete_tree(t_ast *tree)
{
	t_ast_n	*node;

	if (!tree)
		return ;
	if (tree->root)
		ft_delete(tree, tree->root);
	free(tree);
}

static void	ft_delete(t_ast *tree, t_ast_n *node)
{
	if (node)
	{
		ft_delete(tree, node->left);
		ft_delete(tree, node->right);
		free(node);
		node = NULL;
		tree->root--;
	}
}
