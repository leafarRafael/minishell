/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_delimiters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:37:26 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/08 15:48:00 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_words.h"

int	ft_d_quotes(char current)
{
	return (current == '"');
}

int	ft_s_quotes(char current)
{
	return (current == '\'');
}