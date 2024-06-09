/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:03:17 by tforster          #+#    #+#             */
/*   Updated: 2024/06/09 19:02:57 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mini_utils.h"
#include "sigaction.h"

void	init_signal(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_action;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_action(int sig)
{
	printf("SIG = [%d]\n", sig);
	printf("STATUS = [%d]\n", g_status_child);
	g_status_child = 128 + sig;
	// if (env->redisplay == 2)
	// 	close(STDIN_FILENO);
	ft_putstr("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	// if (!env->redisplay)
	// {
		print_pwd();
		ft_putstr_fd("\n", 0);
		rl_redisplay();
	// }
}

void handle_sigint(int sig)
{
	g_status_child = 99;
	printf("Caught signal %d, simulating EOF\n", sig);
}
