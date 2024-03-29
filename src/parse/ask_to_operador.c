/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_to_operador.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:44:39 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/29 10:44:57 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_have_operator(t_lst *lst)
{
	t_var	var;

	var.current_node = lst->head;
	var.i = 1;
	while (var.i <= lst->size)
	{
		if (is_operator(var.current_node->type))
			return (-1);
		var.i++;
		var.current_node = var.current_node->next;
	}
	return (0);
}