/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:36:12 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/26 11:38:53 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(int pipe[2])
{
	dup2(pipe[0], STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
}

