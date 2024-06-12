/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:25:37 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/12 14:30:31 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_msg_error(char *invalid_input, char *msg_error)
{
	write(STDERR_FILENO, " minishell :", ft_strlen(" minishell :"));
	write(STDERR_FILENO, invalid_input, ft_strlen(invalid_input));
	write(STDERR_FILENO, " :", 2);
	write(STDERR_FILENO, msg_error, ft_strlen(msg_error));
	write(STDERR_FILENO, "\n", 2);
}

void	ft_msg_error_lst(char *function, t_lst *input_lst, char *msg_error)
{
	write(STDERR_FILENO, " minishell :", ft_strlen(" minishell :"));
	write(STDERR_FILENO, function, ft_strlen(function));
	write(STDERR_FILENO, " : \"", ft_strlen(" : \""));
	ft_putlst_fd (input_lst, 1, STDERR_FILENO);
	ft_putstr_fd("\"", STDERR_FILENO);
	write(STDERR_FILENO, "\"", 1);
	write(STDERR_FILENO, msg_error, ft_strlen(msg_error));
}
