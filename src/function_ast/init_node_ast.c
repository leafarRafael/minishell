/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:35:25 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/02 11:25:50 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

t_ast_node	*ft_init_new_ast_node(void)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(t_ast_node));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->m_lst = NULL;
	new_node->type = -42;
	new_node->how_to_exe = -42;
	return (new_node);
}
