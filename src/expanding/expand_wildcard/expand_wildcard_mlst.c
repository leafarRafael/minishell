/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_mlst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 08:46:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/27 14:53:29 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

static int	find_asterisk(t_mlst *mlst);
static void search_replace_token(t_mlst *mlst);
static void replace(t_mlst *mlst, t_llst *line, int *i);

void	expand_wildcard_mlst(t_mlst *mlst)
{
	if (!mlst)
		return ;
	if (mlst->size == 0)
		return ;
	if (mlst->size == 1)
		return ;
	if (find_asterisk(mlst))
		return ;
	search_replace_token(mlst);
}

static int	find_asterisk(t_mlst *mlst)
{
	int		i;
	t_llst	*line;

	i = 1;
	line = mlst->head;
	while (i <= mlst->size)
	{
		if (find_type_return_ptr(line->lst, WILDCARD))
			return (0);
		line = line->next;
		i++;
	}
	return(1);
}

static void search_replace_token(t_mlst *mlst)
{
	t_llst	*nlst;
	t_llst	*next;
	int		i;

	i = 0;
	nlst = mlst->head;
	next = nlst->next;
	while(i < mlst->size)
	{
		if (find_type_return_ptr(nlst->lst, WILDCARD))
			replace(mlst, nlst, &i);
		i++;
		nlst = next;
		next = next->next;
	}
}

static void replace(t_mlst *mlst, t_llst *line, int *i)
{
	t_mlst	*directory;

	directory = expand_current_directory();
	if (!directory)
		return ;
	ft_expand_lst_wildcard(line->lst, directory);
	if (directory->size != 0)
	{
		insert_lnode_between(mlst, line, directory);
		ft_rmv_spcfc_lst_mtrx(mlst, line);
		free(directory);
		(*i)--;
	}
	else
		free(directory);;
}