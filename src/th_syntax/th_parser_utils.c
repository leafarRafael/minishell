/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_paser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:48:36 by tforster          #+#    #+#             */
/*   Updated: 2024/05/12 16:49:14 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_tab(int ch)
{
	if ((7 <= ch && ch <= 13) || ch == ' ')
		return (1);
	return (0);
}

int	ft_is_in_set(char ch, char *set)
{
	while (*set)
	{
		if (ch == *(set++))
			return (1);
	}
	return (0);
}
