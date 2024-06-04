/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_allfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:07:25 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 08:14:29 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_allfd(t_mini *mini)
{
	close(mini->fd_std[0]);
	close(mini->fd_std[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
