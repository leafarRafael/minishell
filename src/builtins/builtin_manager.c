/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:01:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/29 08:54:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int valid_builtin(t_lst *lst);

int	is_builtin(t_ast_n *cmd, t_mini *mini)
{
	t_llst	*line;
	int		i;
	int		nbr_builtin;

	line = cmd->m_lst->matrix->head;
	i = 1;
	while (i <= cmd->m_lst->matrix->size)
	{
		nbr_builtin = 0;
		nbr_builtin = valid_builtin(line->lst);
		if (nbr_builtin)
			return (nbr_builtin);
		line = line->next;
		i++;
	}
	return (0);
}

static int valid_builtin(t_lst *lst)
{
	if (!ft_strlstcmp(lst, CD, lst->size))
		return (1);
	else if (!ft_strlstcmp(lst, PWD, lst->size))
		return (2);
	else if (!ft_strlstcmp(lst, ENV, lst->size))
		return (3);
	else if (!ft_strlstcmp(lst, ECHO, lst->size))
		return (4);
	else if (!ft_strlstcmp(lst, EXIT, lst->size))
		return (5);
	else if (!ft_strlstcmp(lst, UNSET, lst->size))
		return (6);
	else if (!ft_strlstcmp(lst, EXPORT, lst->size))
		return (7);
	return (0);
}
