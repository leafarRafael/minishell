/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:18:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/24 17:31:15 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node *find_head(t_mtrx_lst *m_lst, t_lst *lst);

char	**ft_path_env(t_mtrx_lst *m_lst)
{
	t_lst	*temp;
	t_lst	to_array;

	temp = find_str_in_matrixlst(m_lst, PATH, SIZE_PATH);
	to_array.head = find_head(m_lst, temp);
	to_array.last = temp->last;
	to_array.size = temp->size -SIZE_PATH;
	return (ft_split(ft_cpy_lst_to_array(&to_array), ':'));
}

static t_node *find_head(t_mtrx_lst *m_lst, t_lst *lst)
{
	t_node	*node;
	int		index;
	int		i;

	i = 1;
	index = 0;
	node = lst->head;
	while (i <= lst->size)
	{
		if (node->c == PATH[index])
			index++;
		else
			index = 0;
		if (index == SIZE_PATH)
			break ;
		node = node->next;
		i++;
	}
	return (node->next);
}