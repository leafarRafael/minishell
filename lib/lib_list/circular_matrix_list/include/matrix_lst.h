/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_lst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:34:14 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:26:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_LST_H
# define MATRIX_LST_H

# include <stdlib.h>
# include "array_lst.h"

typedef struct s_lst_line
{
	t_lst				*lst;
	struct s_lst_line	*next;
	struct s_lst_line	*prev;
	int					rdrct;
}				t_lst_line;

typedef struct s_matrix_list
{
	t_lst_line	*head;
	t_lst_line	*last;
	int			size;
}				t_mtrx_lst;

typedef struct s_variables_matrix_list
{
	t_lst_line	*current_lst;
	t_lst_line	*second_lst;
	t_lst_line	*prev_lst;
	t_lst_line	*next_lst;
	t_lst_line	*head_lst;
	t_lst_line	*last_lst;
	char		**matrix;
	int			i;
	int			index;

}				t_var_matrix;

t_mtrx_lst	*ft_init_matrix(void);
t_lst_line	*ft_init_line_lst(void);
int			ft_add_list_front(t_mtrx_lst *matrix_lst, t_lst *lst);
int			ft_add_list_back(t_mtrx_lst *matrix_lst, t_lst *lst);
int			ft_rmv_spcfc_lst_mtrx(t_mtrx_lst *matrix, t_lst_line *line_lst);
int			ft_remove_lst_front(t_mtrx_lst *m_lst);
int			ft_remove_list_back(t_mtrx_lst *m_lst);
int			ft_delete_matrix(t_mtrx_lst *matrix);
char		**ft_cpy_mtrllst_to_cmtrx(t_mtrx_lst *lst_matrix);
t_mtrx_lst	*ft_cmtrix_to_mtrx_lst(char **matrix);
t_lst		*find_str_in_matrixlst(t_mtrx_lst *m_lst, char *str, int size);

#endif