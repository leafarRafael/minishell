/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_allfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:07:25 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/27 13:03:20 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_allfd(t_mini *mini)
{
	if (mini->fd_std[0])
		close(mini->fd_std[0]);
	if (mini->fd_std[1])
		close(mini->fd_std[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
