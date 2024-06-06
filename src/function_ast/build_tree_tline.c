/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_tline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:45:02 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/06 11:52:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "abstract_syntax_tree.h"
#include "matrix_lst.h"

static void	ft_left(t_ast_n *current_node, t_ast_n *new, int value);
static void	ft_right(t_ast_n *current_node, t_ast_n *new, int value);

void	ft_build_tree_lnode(t_ast *tree, t_llst *line, int value)
{
	t_ast_var	v;

	if (!tree || !line)
		return ;
	v.ast_node = ft_init_new_ast_node();
	v.ast_node->line = line;
	tree->size++;
	if (tree->root == NULL)
		tree->root = v.ast_node;
	else
	{
		if (value <= tree->root->line->lex_val)
			ft_left(tree->root, v.ast_node, value);
		else
			ft_right(tree->root, v.ast_node, value);
	}
}

static void	ft_left(t_ast_n *current_node, t_ast_n *new, int value)
{
	if (current_node->left == NULL)
		current_node->left = new;
	else
	{
		if (value <= current_node->left->line->lex_val)
			ft_left(current_node->left, new, value);
		else
			ft_right (current_node->left, new, value);
	}
}

static void	ft_right(t_ast_n *current_node, t_ast_n *new, int value)
{
	if (current_node->right == NULL)
		current_node->right = new;
	else
	{
		if (value > current_node->right->line->lex_val)
			ft_right (current_node->right, new, value);
		else
			ft_left(current_node->right, new, value);
	}
}
