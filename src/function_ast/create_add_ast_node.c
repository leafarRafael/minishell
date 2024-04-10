/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_add_ast_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:29:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/10 15:17:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

int	ft_create_ast_node(t_ast *ast, t_mtrx_lst *matrix)
{
	t_ast_var	v;

	if (!ast)
		return (-1);
	if (!matrix)
		return (-1);
	if (ast->size == 0)
	{
		v.ast_node = ft_init_new_ast_node();
		v.ast_node->m_lst = matrix;
		ast->root = v.ast_node;
	}
	
}
