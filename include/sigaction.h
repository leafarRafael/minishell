/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:07:15 by tforster          #+#    #+#             */
/*   Updated: 2024/06/09 19:03:09 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGACTION_H
# define SIGACTION_H

# include <signal.h>

void	init_signal(void);
void	sigint_action(int sig);
void	handle_sigint(int sig);

#endif
