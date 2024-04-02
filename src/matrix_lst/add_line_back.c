/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:26:15 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/01 10:05:13 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static void	ft_first_line(t_matrix_lst *matrix_lst, t_lst_line *new_line);
static void	ft_second_line(t_matrix_lst *matrix_lst, t_lst_line *new_line);
static void	ft_third_onwards_line(t_matrix_lst *matrix_lst, t_lst_line *new_line);

int	ft_add_list_back(t_matrix_lst *matrix_lst, t_lst *lst)
{
	t_var_matrix	var;
	t_lst_line 		*new_line;

	new_line = ft_init_line_lst();
	if (!new_line)
		return (-1);
	if (!matrix_lst || !lst)
		return (-1);
	new_line->lst = lst;
	if (matrix_lst->size == 0)
	{
		ft_first_line(matrix_lst, new_line);
		return (0);
	}
	else if (matrix_lst->size == 1)
	{
		ft_second_line(matrix_lst, new_line);
		return (0);
	}
	else
	{
		ft_third_onwards_line(matrix_lst, new_line);
		return (0);
	}
	return (-1);
}

static void	ft_first_line(t_matrix_lst *matrix_lst, t_lst_line *new_line)
{
	new_line->next = new_line;
	new_line->prev = new_line;
	matrix_lst->head = new_line;
	matrix_lst->last = new_line;
	matrix_lst->size++;
}

static void	ft_second_line(t_matrix_lst *matrix_lst, t_lst_line *new_line)
{
	new_line->next = matrix_lst->head;
	new_line->prev = matrix_lst->head;
	matrix_lst->head->prev = new_line;
	matrix_lst->head->next = new_line;
	matrix_lst->last = new_line;
	matrix_lst->size++;
}

static void	ft_third_onwards_line(t_matrix_lst *matrix_lst, t_lst_line *new_line)
{
	t_var_matrix	var;

	var.head_lst = matrix_lst->head;
	var.last_lst = matrix_lst->last;
	new_line->next = var.head_lst;
	new_line->prev = var.last_lst;
	var.last_lst->next = new_line;
	var.head_lst->prev = new_line;
	matrix_lst->last = new_line;
	matrix_lst->size++;
}
