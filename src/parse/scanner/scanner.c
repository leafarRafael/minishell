/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:03:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/05 09:08:13 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	scanner_input(t_lst *lst)
{
	t_var_parse	var;

	if (!lst)
		return (-1);
	if (lst->size == 0)
		return (-1);
	var.node = lst->head;
	var.d_quotes = 0;
	var.s_quotes = 0;
	var.i = 1;
	while (var.i <= lst->size)
	{
		if (is_double_quotes(var.node->c))
		{
			if (var.d_quotes == 1)
				var.d_quotes--;
			else
				var.d_quotes++;
		}

		var.node = var.node->next;
		var.i++;
	}
}