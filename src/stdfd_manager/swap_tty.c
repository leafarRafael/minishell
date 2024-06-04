/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_tty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:02:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:54:18 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_tty(int copy_restore, t_mini *mini)
{
	if (copy_restore == COPY)
	{
		mini->fd_std[0] = dup(STDIN_FILENO);
		mini->fd_std[1] = dup(STDOUT_FILENO);
	}
	if (copy_restore == RESTORE)
	{
		dup2(mini->fd_std[0], STDIN_FILENO);
		dup2(mini->fd_std[1], STDOUT_FILENO);
	}
}
