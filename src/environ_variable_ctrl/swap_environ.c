/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:24:11 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:52:22 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap_environ(t_mini *mini, int swap_restore)
{
	if (swap_restore == SWAP)
	{
		mini->env = ft_cpy_mtrllst_to_cmtrx(mini->m_lst_env);
		mini->temp_environ = __environ;
		__environ = mini->env;
	}
	if (swap_restore == RESTORE)
	{
		__environ = mini->temp_environ;
		ft_delcmtrx(mini->env);
	}
}
