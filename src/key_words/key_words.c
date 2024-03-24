/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:14:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/24 10:40:15 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "key_words.h"

int	ft_is_here_doc(char current, char next)
{
	return (current == '<' && next == '<');
}

int	ft_is_append(char current, char next)
{
	return (current == '>' && next == '>');
}

int	ft_is_or(char current, char next)
{
	return (current == '|' && next == '|');
}

int	ft_is_and(char current, char next)
{
	return (current == '&' && next == '&');
}

int	is_white_space(char c)
{
	return (c == ' ' || c == '	');
}