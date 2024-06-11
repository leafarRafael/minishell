/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:07:15 by tforster          #+#    #+#             */
/*   Updated: 2024/06/11 11:32:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGACTION_H
# define SIGACTION_H

# include <signal.h>

# define EOF_MSG1 "\nwarning: here-document delimited "
# define EOF_MSG2 "by end-of-file (wanted `eof')\n"

void	init_signal(void);
void	sigint_action(int sig, siginfo_t *siginfo, void *context);
void	here_signal(void);
void	handle_sigint(int sig);

#endif
