/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_delimiters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:15 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/08 15:48:48 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_words.h"

int	ft_space(char current)
{
	return (current == ' ');
}

int	ft_tab(char current)
{
	return (current == '	');
}