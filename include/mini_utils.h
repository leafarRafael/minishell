/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:46:13 by tforster          #+#    #+#             */
/*   Updated: 2024/06/10 14:32:53 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_UTILS_H
# define MINI_UTILS_H

# include "minishell.h"

void	init_minishell(t_mini *mini);
void	print_pwd(void);
char	*sig_eof(char *str);

#endif
