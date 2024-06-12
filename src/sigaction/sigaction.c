/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:03:17 by tforster          #+#    #+#             */
/*   Updated: 2024/06/12 16:22:12 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mini_utils.h"
#include "sigaction.h"

void	init_signal(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = sigint_action;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_action(int sig, siginfo_t *siginfo, void *context)
{
	if (context)
		context = NULL;
	else
		context = NULL;
	g_status_child = 128 + sig;
	ft_putstr("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (siginfo->si_pid != 0)
	{
		print_pwd();
		ft_putstr_fd("\n", 0);
		rl_redisplay();
	}
}

void	here_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_sigint(int sig)
{
	ft_putstr_fd("\n", 2);
	if (sig)
		g_status_child = 99;
	else
		g_status_child = 99;
	sig = 0;
}
