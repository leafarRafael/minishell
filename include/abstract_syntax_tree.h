/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 08:23:08 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/10 14:43:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_H
# define ABSTRACT_SYNTAX_TREE_H

# include "matrix_lst.h"

typedef struct s_ast_node
{
	t_mtrx_lst		*m_lst;
	int					type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}			t_ast_node;

typedef struct s_ast
{
	struct s_ast	*root;
	int				size;
}				t_ast;

typedef struct s_ast_var
{
	t_ast_node		*ast_node;
	t_ast			*new_ast;
}				t_ast_var;


int			ft_create_ast_node(t_ast *ast, t_mtrx_lst *matrix, int type);
t_ast		*ft_init_ast();
t_ast_node	*ft_init_new_ast_node();

#endif