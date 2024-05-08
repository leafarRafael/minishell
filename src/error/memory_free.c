/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:08:21 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/08 13:33:05 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int free_memory(t_mini *mini, t_var_exe	*var, t_ast *ast)
{
	int i;

	i = 0;
	if (mini)
	{
		if (mini->mmlst)
			i += ft_delete_mmlst(mini->mmlst);
		if (mini->m_lst_env)
			i += ft_delete_matrix(mini->m_lst_env);
	}
	if (ast)
	{
		ft_delete_tree(ast);
		if (ast != NULL)
			i++;
	}
	if (var)
	{
		if (var->env)
			i += ft_delete_cmatrix(var->env);
		if (var->command_m)
			i += ft_delete_cmatrix(var->command_m);
		if (var->path_exe)
			free(var->path_exe);
	}
	return (i);
}