/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:31:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/27 12:56:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void delete_white_space(t_lst *lst);

t_mlst	*ft_token_cmd(t_lst	*lst)
{
	t_mlst		*new_matrix;

	if (!lst)
		return (NULL);
	if (lst->size == 0)
		return (NULL);
	delete_white_space(lst);
	new_matrix = init_mlst();
	if (!new_matrix)
		return (NULL);
	if (lst->head->type == OPEN_PAREN)
	{
		token_parent(lst, new_matrix);
		return (new_matrix);
	}
	if (is_operator(lst->head->type))
	{
		token_operator(lst, new_matrix);
		return (new_matrix);
	}
	token_command(lst, new_matrix);
	return (new_matrix);
}

static void delete_white_space(t_lst *lst)
{
	while (lst->last->type == WH_SPACE)
		lst_rmv_back(lst);
	while (lst->head->type == WH_SPACE)
		ft_remove_node_front(lst);
}
