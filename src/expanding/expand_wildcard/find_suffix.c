/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_suffix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:46:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/03 15:03:57 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

int	find_sufix(t_lst *inlst, t_lst *this_lst)
{
	if (this_lst->size == 1 && this_lst->last->type == WILDCARD)
		return (ft_delete_list(inlst) + ft_delete_list(this_lst));
	while(this_lst->last->type != WILDCARD)
	{
		if (inlst->size == 0)
			return (ft_delete_list(inlst) + ft_delete_list(this_lst) +1);
		if (inlst->last->c != this_lst->last->c)
			return (ft_delete_list(inlst) + ft_delete_list(this_lst) +1) ;
		lst_rmv_back(this_lst);
		lst_rmv_back(inlst);
	}
	return (find_infix(inlst, this_lst));
}
