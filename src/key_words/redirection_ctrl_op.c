/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_ctrl_op.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:30:29 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:40:41 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_words.h"

int	ft_heredoc(char current, char next)
{
	return (current == '<' && next == '<');
}

int	ft_append(char current, char next)
{
	return (current == '>' && next == '>');
}

int	ft_infile(char current)
{
	return (current == '<');
}

int	ft_outfile(char current)
{
	return (current == '>');
}
