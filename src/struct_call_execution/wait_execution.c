/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:44:09 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/12 19:45:20 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_status(t_ncllc *no, t_mini *mini);

void	ft_wait_execution(t_mini *mini)
{
	int		i;
	t_ncllc	*no;

	g_status_child = 0;
	if (!mini->collect || !mini->collect->head)
		return ;
	no = mini->collect->head;
	i = 0;
	while (i < mini->collect->size)
	{
		if (no->type.pid != -42)
			add_status(no, mini);
		no = no->next;
		i++;
	}
	g_status_child = mini->collect->last->status;
}

static void	add_status(t_ncllc *no, t_mini *mini)
{
	waitpid(no->type.pid, &mini->status, WUNTRACED);
	if (WIFSIGNALED(mini->status))
	{
		if (WTERMSIG(mini->status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			no->status = 128 + WTERMSIG(mini->status);
		}
	}
	else
		no->status = WEXITSTATUS(mini->status);
	if (WTERMSIG(mini->status) == SIGINT)
		no->status = 128 + WTERMSIG(mini->status);
}
