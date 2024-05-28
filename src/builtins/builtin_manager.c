/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:01:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/28 12:29:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int valid_builtin(t_lst *lst);
int	ft_find_str_inlist2(t_lst *lst, char *str, int size);

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
	if (!ft_find_str_inlist2(lst, CD, lst->size))
		return (1);
	else if (!ft_find_str_inlist2(lst, PWD, lst->size))
		return (2);
	else if (!ft_find_str_inlist2(lst, ENV, lst->size))
		return (3);
	else if (!ft_find_str_inlist2(lst, ECHO, lst->size))
		return (4);
	else if (!ft_find_str_inlist2(lst, EXIT, lst->size))
		return (5);
	else if (!ft_find_str_inlist2(lst, UNSET, lst->size))
		return (6);
	else if (!ft_find_str_inlist2(lst, EXPORT, lst->size))
		return (7);
	return (0);
}


int	ft_find_str_inlist2(t_lst *lst, char *str, int size)
{
	t_var	v;
	char	*new;
	int		i;

	i = 0;
	new = ft_cpy_lst_to_array(lst);
	i = memcmp(str, new, size);
	free(new);
	return (i);
}