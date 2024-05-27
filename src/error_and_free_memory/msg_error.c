/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:25:37 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/22 09:02:42 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_msg_error(char *invalid_input, char *msg_error)
{
/* 	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO); */
	ft_putstr_fd(invalid_input, STDERR_FILENO);
	ft_putstr_fd(" :", STDERR_FILENO);
	ft_putstr_fd(msg_error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}