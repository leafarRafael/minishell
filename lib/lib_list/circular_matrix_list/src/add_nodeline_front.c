/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_nodeline_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:17:10 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/24 16:52:06 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static void	ft_first_matrix_node(t_mlst *mlst, t_llst *lnode);
static void	ft_second_matrix_node(t_mlst *mlst, t_llst *lnode);
static void	ft_third_onwards_matrix_node(t_mlst *mlst, t_llst *lnode);

int	ft_add_mlstnode_front(t_mlst *mlst, t_llst *lnode)
{
	if (!mlst)
		return (-1);
	if (mlst->size == 0)
	{
		ft_first_matrix_node(mlst, lnode);
		return (0);
	}
	else if (mlst->size == 1)
	{
		ft_second_matrix_node(mlst, lnode);
		return (0);
	}
	else
	{
		ft_third_onwards_matrix_node(mlst, lnode);
		return (0);
	}
}

static void	ft_first_matrix_node(t_mlst *mlst, t_llst *lnode)
{
	lnode->next = lnode;
	lnode->prev = lnode;
	mlst->head = lnode;
	mlst->last = lnode;
	mlst->size = 1;
}

static void	ft_second_matrix_node(t_mlst *mlst, t_llst *lnode)
{
	lnode->next = mlst->last;
	lnode->prev = mlst->last;
	mlst->last->prev = lnode;
	mlst->last->next = lnode;
	mlst->head = lnode;
	mlst->size++;
}

static void	ft_third_onwards_matrix_node(t_mlst *mlst, t_llst *lnode)
{
	t_var_matrix	var;

	var.current_lst = mlst->head;
	var.current_lst = mlst->head;
	lnode->next = var.current_lst;
	lnode->prev = mlst->last;
	mlst->last->next = lnode;
	var.current_lst->prev = lnode;
	mlst->head = lnode;
	mlst->size++;
}
