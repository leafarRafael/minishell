/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_mlst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:40:13 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 09:47:52 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

void	ft_remove_quote_mlst(t_mlst *mlst)
{
	int		counter;
	t_llst	*current;
	t_llst	*next;

	if (!mlst)
		return ;
	if (mlst->size == 0)
		return ;
	current = mlst->head;
	next = current->next;
	counter = 1;
	while (counter <= mlst->size)
	{
		if (current->lst->size != 0)
			ft_remove_quotes_lst(current->lst);
		if (mlst->size == 0)
			break ;
		current = next;
		next = next->next;
		counter++;
	}
}
