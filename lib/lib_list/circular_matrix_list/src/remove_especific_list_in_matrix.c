/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_especific_list_in_matrix.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 08:58:39 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/15 12:27:36 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static int	ft_check_in_matrix(t_mtrx_lst *matrix, t_lst_line *line_lst);
static int	ft_other_cases(t_mtrx_lst *matrix, t_lst_line *line_list);

int	ft_remove_especific_lst_mtrx(t_mtrx_lst *matrix, t_lst_line *line_lst)
{
	if (!matrix)
		return(-1);
	if (!line_lst)
		return (-1);
	if (ft_check_in_matrix(matrix, line_lst))
		return (-1);
	if (matrix->head == line_lst)
		return (ft_remove_lst_front(matrix));
	if (matrix->last == line_lst)
		return (ft_remove_list_back(matrix));
	if (matrix->head != line_lst || matrix->last != line_lst)
		return (ft_other_cases(matrix, line_lst));
	return (-1);
}

static int	ft_check_in_matrix(t_mtrx_lst *matrix, t_lst_line *line_lst)
{
	t_var_matrix	v;

	v.i = 1;
	v.current_lst = matrix->head;
	while (v.i <= matrix->size)
	{
		if (v.current_lst == line_lst)
			return (0);
		v.current_lst = v.current_lst->next;
		v.i++;
	}
	return (-1);
}

static int ft_other_cases(t_mtrx_lst *matrix, t_lst_line *line_list)
{
	t_var_matrix	v;

	v.prev_lst = line_list->prev;
	v.next_lst = line_list->next;
	v.prev_lst->next = v.next_lst;
	v.next_lst->prev = v.prev_lst;
	matrix->size--;
	if (ft_delete_list(line_list->lst))
		return (-1);
	free(line_list);
	line_list = NULL;
	return (0);
}