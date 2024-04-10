/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_ctrl_op.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:30:29 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/08 15:49:08 by rbutzke          ###   ########.fr       */
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