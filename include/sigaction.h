/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:07:15 by tforster          #+#    #+#             */
/*   Updated: 2024/06/10 21:12:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGACTION_H
# define SIGACTION_H

# include <signal.h>

void	init_signal(void);
void	sigint_action(int sig, siginfo_t *siginfo, void *context);
void	here_signal(void);
void	handle_sigint(int sig);

#endif
