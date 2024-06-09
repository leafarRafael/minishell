/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:26:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 11:35:07 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	ft_status_builtin(t_mini *mini, int value, int error_or_success)
{
	if (error_or_success == INIT_SUCCESS)
	{
		g_status_child = value;
		mini->collect->last->status = value;
	}
	if (error_or_success == __ERROR)
	{
		g_status_child = value;
		mini->collect->last->status = value;
	}
}
