/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_lst2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:53:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/26 10:39:16 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

int		ft_find_infix(t_mlst	*mlst, char *str, int (*func) (t_lst *, char *, int ));

void	ft_expand_lst_wildcard2(t_lst *lst, t_mlst *dir_content)
{
	t_node	*asterisk;
	t_node	*temp;
	char	*prefix;
	char	*suffix;
	int		i;

	asterisk = find_type_return_ptr(lst, WILDCARD);
	if (!asterisk)
		return ;
	if (lst->size == 1)
	{
		asterisk->type = META_LITERAL;
		return ;
	}
	prefix = NULL;
	suffix = NULL;
	temp = asterisk;
	prefix = get_prefix(asterisk, lst);
	suffix = get_suffix(asterisk, lst);
	if (prefix)
		ft_find_infix(dir_content, prefix, ft_find_head);
	if (suffix)
		ft_find_infix(dir_content, suffix, ft_find_last);
	asterisk->type = META_LITERAL;
}

int	ft_find_infix(t_mlst	*mlst, char *str, int (*func) (t_lst *, char *, int ))
{
	t_llst	*lnode;
	t_llst	*lnnext;
	int		i;

	i = 0;
	lnode = mlst->head;
	lnnext = lnode->next;
	while (i < mlst->size)
	{
		if (!func(lnode->lst, str, ft_strlen(str)))
		{
			ft_rmv_spcfc_lst_mtrx(mlst, lnode);
			i--;
		}
		i++;
		lnode = lnode->next;
		lnnext = lnnext->next;
	}
	if (mlst->size == 0)
		return (1);
	return (0);
}

static int	find_prefix(t_lst *inlst, t_lst *this_lst);
static int	find_sufix(t_lst *inlst, t_lst *this_lst);

void	ft_expand_lst_wildcard(t_lst *lst, t_mlst *dir_content)
{
	t_llst	*current;
	t_llst	*next;
	t_lst	*cpy;
	int		i;

	current = dir_content->head;
	next = current->next;
	i = 1;
	while (i <= dir_content->size)
	{
		cpy = ft_duplst(lst, ft_cpynode, ft_add_node_back);
		if (find_prefix(current->lst, cpy))
		{
			ft_rmv_spcfc_lst_mtrx(dir_content, current);
			i--;
		}
		if (dir_content->size == 0)
			break ;
		current = next;
		next = next->next;
		i++;
	}
}

static int	find_prefix(t_lst *inlst, t_lst *this_lst)
{
	t_lst	*cpy;

	if (!inlst || !this_lst)
		return (1);
	if (this_lst->size == 1 && this_lst->head->type == WILDCARD)
		return (ft_remove_node_front(this_lst));
	cpy = ft_duplst(inlst, ft_cpynode, ft_add_node_back);
	while(this_lst->head->type != WILDCARD)
	{
		if (cpy->head->c != this_lst->head->c)
			return (1);
		ft_remove_node_front(this_lst);
		ft_remove_node_front(cpy);
	}
	return (find_sufix(cpy, this_lst));
}

static int	find_sufix(t_lst *inlst, t_lst *this_lst)
{
	t_lst	*cpy;

	if (!inlst || !this_lst)
		return (1);
	if (this_lst->size == 1 && this_lst->last->type == WILDCARD)
		return (ft_remove_node_back(this_lst));
	cpy = ft_duplst(inlst, ft_cpynode, ft_add_node_back);
	ft_delete_list(inlst);
	while(this_lst->last->type != WILDCARD)
	{
		if (cpy->last->c != this_lst->last->c)
			return (1);
		ft_remove_node_back(this_lst);
		ft_remove_node_back(cpy);
	}
	return (0);
}