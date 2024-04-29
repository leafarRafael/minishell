/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:31:25 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 17:08:12 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_memory_revert_environ(t_var_minishell *v)
{
	ft_delete_tree(v->ast);
	ft_delete_mtrx_mtrx_lst(v->list_matrix);
	free(v->input_user);
	v->looping_shell = ft_exit(v->infile);
	free(v->infile);
	__environ = v->temp__environ;
}
