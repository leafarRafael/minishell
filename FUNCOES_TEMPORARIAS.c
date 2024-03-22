/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FUNCOES_TEMPORARIAS.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:26:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 14:27:15 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_array_lst(t_array_lst *lst, int front_back)
{
	int i;
	t_node_alst *temp;

	if (!lst)
		return ;
	if (!lst->head && !lst->last)
		return ;
	i = 0;
	if (front_back == 0)
		temp = lst->head;
	else
		temp = lst->last;
	while (i != lst->size)
	{
		printf("%c", temp->c);
		if (front_back == 0)
			temp = temp->next;
		else
			temp = temp->prev;
		i++;
	}
}