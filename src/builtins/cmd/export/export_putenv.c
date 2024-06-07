/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_putenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:16:40 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/07 10:38:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	ft_put_export(t_ast_n *root);

void	export_putenv(t_mini *mini)
{
	t_builtin	v;

	v.line = mini->m_lst_env->head;
	v.index = 1;
	v.expor_sort = ft_init_ast();
	add_lexicographic_value(mini->m_lst_env, '=');
	while (v.index <= mini->m_lst_env->size)
	{
		ft_build_tree_lnode(v.expor_sort, v.line, v.line->lex_val);
		v.line = v.line->next;
		v.i_color++;
		v.index++;
	}
	ft_putstr_fd(mini->color[2], STDOUT_FILENO);
	ft_put_export(v.expor_sort->root);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_delete_tree(v.expor_sort);
}

static void	ft_put_export(t_ast_n *root)
{
	if (root != NULL)
	{
		ft_put_export(root->left);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putlst_fd(root->line->lst, 1, STDOUT_FILENO);
		ft_put_export(root->right);
	}
}
