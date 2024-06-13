/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_var_declaration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:13:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/13 15:55:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	valid_infix(char c);
static int	valid_prefix(char c);

int	valid_var_declar(t_lst *lst)
{
	t_node	*node;
	int		i;

	if (!lst)
		return (1);
	if (lst->size == 0)
		return (1);
	if (!valid_prefix(lst->head->c))
		return (1);
	if (lst->size == 2 && lst->head->next->c == '=')
		return (0);
	i = 1;
	node = lst->head->next;
	while (i < lst->size && node->c != '=')
	{
		if (!valid_infix(node->c))
			return (1);
		node = node->next;
		i++;
	}
	return (0);
}

static int	valid_prefix(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c == '_'));
}

static int	valid_infix(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| (c == '_'));
}
