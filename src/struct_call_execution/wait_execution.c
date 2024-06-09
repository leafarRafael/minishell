/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:44:09 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 11:19:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_execution(t_mini *mini)
{
	int			i;
	t_ncollec	*no;

	no = mini->collect->head;
	i = 0;
	while (i < mini->collect->size)
	{
		if (no->type.pid != -42)
		{
			waitpid(no->type.pid, &mini->status, WUNTRACED);
			if (WIFSIGNALED(mini->status))
			{
				if (WTERMSIG(mini->status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", 2);
				no->status = 128 + WTERMSIG(mini->status);
			}
			else
				no->status = WEXITSTATUS(mini->status);
		}
		no = no->next;
		i++;
	}
	g_status_child = mini->collect->last->status;
}
