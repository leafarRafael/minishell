/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_delimiters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:15 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:41:17 by rbutzke          ###   ########.fr       */
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

int	ft_words_delemiter(char current)
{
	return (ft_space(current) || ft_tab(current));
}
