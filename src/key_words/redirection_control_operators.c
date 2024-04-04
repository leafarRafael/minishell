/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_control_operators.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:30:29 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 12:53:38 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_words.h"

int	ft_is_here_doc(char current, char next)
{
	return (current == '<' && next == '<');
}

int	ft_is_append(char current, char next)
{
	return (current == '>' && next == '>');
}

int	ft_is_infile(char current)
{
	return (current == '<');
}

int	ft_is_outfile(char current)
{
	return (current == '>');
}