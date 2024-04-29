/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:26:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:40:33 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_words.h"

int	ft_or_op(char current, char next)
{
	return (current == '|' && next == '|');
}

int	ft_and_op(char current, char next)
{
	return (current == '&' && next == '&');
}

int	is_pipe(char c)
{
	return (c == '|');
}
