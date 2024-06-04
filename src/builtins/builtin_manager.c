/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:01:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 17:37:30 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	valid_builtin(t_lst *lst);

int	is_builtin(t_ast_n *cmd)
{
	t_llst	*line;
	int		i;
	int		nbr_builtin;

	line = cmd->m_lst->matrix->head;
	i = 0;
	while (i <= cmd->m_lst->matrix->size)
	{
		if (line->rdrct == -42)
		{
			nbr_builtin = 0;
			nbr_builtin = valid_builtin(line->lst);
			return (nbr_builtin);
		}
		line = line->next;
		i++;
	}
	return (0);
}

static int	valid_builtin(t_lst *lst)
{
	if (!ft_strlstcmp(lst, CD))
		return (1);
	else if (!ft_strlstcmp(lst, PWD))
		return (2);
	else if (!ft_strlstcmp(lst, ENV))
		return (3);
	else if (!ft_strlstcmp(lst, ECHO))
		return (4);
	else if (!ft_strlstcmp(lst, EXIT))
		return (5);
	else if (!ft_strlstcmp(lst, UNSET))
		return (6);
	else if (!ft_strlstcmp(lst, EXPORT))
		return (7);
	return (0);
}
