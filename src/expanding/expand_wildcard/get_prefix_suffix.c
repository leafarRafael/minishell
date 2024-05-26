/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prefix_suffix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 08:44:33 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/26 08:44:50 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

char	*get_prefix(t_node *ptr, t_lst *lst)
{
	t_node	*temp;
	t_lst	*lst_prefix;
	char	*prefix;

	if (!lst || !ptr)
		return (NULL);
	if (ptr == lst->head)
		return (NULL);
	temp = ptr->prev;
	lst_prefix = ft_init_lst();
	while (1)
	{
		ft_add_node_front(lst_prefix, ft_cpynode(temp));
		temp = temp->prev;
		if (temp == lst->last)
			break ;
		if (temp->type == WILDCARD)
			break ;
		if (temp->type != NO_OP_TYPE)
			break ;
	}
	prefix = ft_cpy_lst_to_array(lst_prefix);
	ft_delete_list(lst_prefix);
	return (prefix);
}

char	*get_suffix(t_node *ptr, t_lst *lst)
{
	t_node	*temp;
	t_lst	*lst_suffix;
	char	*suffix;

	if (!lst || !ptr)
		return (NULL);
	if (ptr == lst->last)
		return (NULL);
	temp = ptr->next;
	lst_suffix = ft_init_lst();
	while (1)
	{
		ft_add_node_back(lst_suffix, ft_cpynode(temp));
		temp = temp->next;
		if (temp == lst->head)
			break ;
		if (temp->type == WILDCARD)
			break ;
		if (temp->type != NO_OP_TYPE)
			break ;
	}
	suffix = ft_cpy_lst_to_array(lst_suffix);
	ft_delete_list(lst_suffix);
	return (suffix);
}

