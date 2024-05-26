/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_mlst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 08:46:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/26 12:46:57 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

void	expand_wildcard_mlst(t_mlst *mlst)
{
	t_llst	*nlst;
	t_llst	*next;
	t_mlst	*asteric_expand;
	int		i;

	i = 0;
	nlst = mlst->head;
	next = nlst->next;
	asteric_expand = expand_current_directory();
	while(i < mlst->size)
	{
		if (find_type_return_ptr(nlst->lst, WILDCARD))
		{
			ft_expand_lst_wildcard(nlst->lst, asteric_expand);
			if (asteric_expand->size != 0)
			{
				insert_lnode_between(mlst, nlst, asteric_expand);
				ft_rmv_spcfc_lst_mtrx(mlst, nlst);
				free(asteric_expand);
				i = 0;
				nlst = mlst->head;
				next = nlst->next;
			}
		}
		i++;
		nlst = next;
		next = next->next;
	}
}
