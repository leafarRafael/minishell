/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_system_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:18:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:50:38 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*find_head(t_mlst *m_lst, t_lst *lst);

char	**path_system_bin(t_mlst *m_lst)
{
	t_lst	*temp;
	t_lst	to_array;
	char	**env;
	char	*array_env;

	if (!m_lst)
		return (NULL);
	env = NULL;
	temp = find_str_in_matrixlst(m_lst, PATH, SIZE_PATH);
	to_array.head = find_head(m_lst, temp);
	to_array.last = temp->last;
	to_array.size = temp->size - SIZE_PATH;
	array_env = ft_cpy_lst_to_array(&to_array);
	env = ft_split(array_env, ':');
	free(array_env);
	return (env);
}

static t_node	*find_head(t_mlst *m_lst, t_lst *lst)
{
	t_node	*node;
	int		index;
	int		i;

	if (!lst)
		return (NULL);
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
