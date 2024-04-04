/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_delimiters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:37:26 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 12:38:48 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_words.h"

int	is_double_quotes(char current)
{
	return (current == '"');
}

int	is_simple_quotes(char current)
{
	return (current == '\'');
}