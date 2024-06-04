/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_after_expandig.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:00:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:56:25 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "minishell.h"

void	token_after_expand(t_mlst *mlst, t_llst *llist)
{
	t_mlst	*new_token;
	t_lst	*cpy;

	if (llist->lst->head->type != D_QUOTES)
	{
		cpy = ft_duplst(llist->lst, ft_cpynode, ft_add_node_back);
		new_token = ft_token_cmd(cpy);
		insert_lnode_between(mlst, llist, new_token);
		free(new_token);
		free(cpy);
		ft_rmv_spcfc_lst_mtrx(mlst, llist);
	}
}
