/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_lst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:53:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/27 15:47:41 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

void	ft_expand_lst_wildcard(t_lst *lst, t_mlst *dir_content)
{
	t_llst	*current;
	t_llst	*next;
	int		i;

	current = dir_content->head;
	next = current->next;
	i = 1;
	while (i <= dir_content->size)
	{
		if (find_prefix(current->lst, lst))
		{
			ft_rmv_spcfc_lst_mtrx(dir_content, current);
			if (dir_content->size == 0)
				break ;
			i--;
		}
		current = next;
		next = next->next;
		i++;
	}
}
