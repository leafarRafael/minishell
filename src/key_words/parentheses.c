/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:03:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 13:05:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_words.h"

int	is_open_parenthesis(char c)
{
	return (c == '(');
}

int	is_close_parenthesis(char c)
{
	return (c == ')');
}