/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:39 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/09 09:04:20 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mnode *find_ptr_op(t_mmlst *mmlst, t_mnode *ptr, int next_or_prev, int op);

void	ft_populetree_left(t_ast *tree, t_mmlst *mmlst)
{
	t_mnode *temp;
	int i;
	int type;

	i = 1;
	temp = mmlst->last;
	type = temp->type;
	while (i <= mmlst->size)
	{
		if (!is_operator(type))
		{
			if (temp->in_tree == -42)
				ft_tree_add_left(tree, temp);
		}
		temp = temp->prev;
		type = temp->type;
		i++;
	}
}

void	ft_populetree_right(t_ast *tree, t_mmlst *mmlst)
{
	t_mnode *temp;
	int i;
	int type;

	i = 1;
	temp = mmlst->last;
	type = temp->type;
	while (i <= mmlst->size)
	{
		if (!is_operator(type))
			ft_tree_add_right(tree, temp);
		temp = temp->prev;
		type = temp->type;
		i++;
	}
}

void	ft_define_ast(t_ast *tree, t_mmlst *mmlst)
{
	t_mnode	*new_ptr;
	t_mnode	*next;

	new_ptr = find_ptr_op(mmlst, mmlst->last, 1, OR_OP | AND_OP);
	if (new_ptr == NULL)
		new_ptr = find_ptr_op(mmlst, mmlst->last, 1, PIPE);
	if (new_ptr == NULL)
		new_ptr = mmlst->head;
	ft_tree_add_left(tree, new_ptr);
}

static t_mnode *find_ptr_op(t_mmlst *mmlst, t_mnode *ptr, int next_or_prev, int op)
{
	t_mnode *temp;
	t_mnode *or_and_ptr;
	int i;
	int	find;
	int type;

	i = 1;
	find = 0;
	temp = ptr;
	type = temp->type;
	or_and_ptr = NULL;
	while (i <= mmlst->size)
	{
		if (type & op && find == 0)
		{
			or_and_ptr = temp;
			find++;	
		}
		if (next_or_prev == 1)
			temp = temp->prev;
		else if (next_or_prev == 2)
			temp = temp->next;
		else
			return (NULL);
		type = temp->type;
		i++;
	}
	return (or_and_ptr);
}