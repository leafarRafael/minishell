/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_prefix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:44:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/27 15:45:25 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

int	find_prefix(t_lst *inlst, t_lst *this_lst)
{
	t_lst	*inlst_cpy;
	t_lst	*this_cpy;

	if (!inlst || !this_lst)
		return (1);
	if (this_lst->size == 1 && this_lst->head->type == WILDCARD)
		return (0);
	inlst_cpy = ft_duplst(inlst, ft_cpynode, ft_add_node_back);
	this_cpy = ft_duplst(this_lst, ft_cpynode, ft_add_node_back);
	while(this_cpy->head->type != WILDCARD)
	{
		if (inlst_cpy->size == 0)
			return (1);
		if (inlst_cpy->head->c != this_cpy->head->c)
			return (1) ;
		ft_remove_node_front(this_cpy);
		ft_remove_node_front(inlst_cpy);
	}
	return (find_sufix(inlst_cpy, this_cpy));
}