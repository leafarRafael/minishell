/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:47:02 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 09:52:44 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	ft_scanner_env(t_mlst *mlst)
{
	t_llst	*node;
	int		i;

	node = mlst->head;
	i = 0;
	while (i < mlst->size)
	{
		ft_scanner_input(node->lst);
		node = node->next;
		i++;
	}
}
