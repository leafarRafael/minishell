/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:46:13 by tforster          #+#    #+#             */
/*   Updated: 2024/06/09 14:16:11 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_UTILS_H
# define MINI_UTILS_H

#include "minishell.h"

void	init_minishell(t_mini *mini);
void	print_pwd(void);
char	*sig_eof(char *str);

#endif
