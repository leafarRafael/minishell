/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:29:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/16 11:28:42 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

static void ft_insert_left(t_ast_node *current_node, t_ast_node *new, int value);
static void ft_insert_right(t_ast_node *current_node, t_ast_node *new, int value);

void	ft_build_tree(t_ast *tree, t_mnode *matrix, int value)
{
	t_ast_var	v;

	if (!tree)
		return ;
	if (!matrix)
		return ;
	v.ast_node = ft_init_new_ast_node();
	v.ast_node->m_lst = matrix;
	tree->size++;
	if (tree->root == NULL)
		tree->root = v.ast_node;
	else
	{
		if (value < tree->root->type)
			ft_insert_left(tree->root, v.ast_node, value);
		else 
			ft_insert_right(tree->root, v.ast_node, value);
	}
}

static void ft_insert_left(t_ast_node *current_node, t_ast_node *new, int value)
{
	if (current_node->left == NULL)
		current_node->left = new;
	else
	{
		if (current_node->left->type < value)
			ft_insert_left(current_node->left, new, value);
		else
			ft_insert_right (current_node->left, new, value);
	}
}

static void ft_insert_right(t_ast_node *current_node, t_ast_node *new, int value)
{
	if (current_node->right == NULL)
		current_node->right = new;
	else
	{
		if (current_node->right->type > value)
			ft_insert_right (current_node->right, new, value);
		else
			ft_insert_left(current_node->right, new, value);
	}
}