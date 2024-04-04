/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_delimiters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:15 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 12:45:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_words.h"

int	is_white_space(char current)
{
	return (current == ' ');
}

int	is_tab_character(char current)
{
	return (current == '	');
}