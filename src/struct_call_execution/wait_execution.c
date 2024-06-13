/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:44:09 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/13 08:53:19 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_status(t_ncllc *no, t_mini *mini, int flag);

void	ft_wait_execution(t_mini *mini)
{
	int		i;
	t_ncllc	*no;

	if (mini->collect->last->type.pid != -42)
		add_status(mini->collect->last, mini, WUNTRACED);
	g_status_child = 0;
	if (!mini->collect || !mini->collect->head)
		return ;
	no = mini->collect->head;
	i = 0;
	while (i < mini->collect->size)
	{
		if (no->type.pid != -42)
			add_status(no, mini, WNOHANG);
		no = no->next;
		if (no == mini->collect->last)
			break ;
		i++;
	}
	g_status_child = mini->collect->last->status;
}

static void	add_status(t_ncllc *no, t_mini *mini, int flag)
{
	waitpid(no->type.pid, &mini->status, flag);
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
