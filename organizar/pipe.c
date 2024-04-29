/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:36:12 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 17:08:29 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(int pipe[2])
{
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
}

void	ft_pipe_parent(int pipe[2])
{
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
	close(pipe[1]);
}
