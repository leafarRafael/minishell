/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_matrix_lst.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:46:47 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/13 12:59:54 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_MATRIX_LST_H
# define MATRIX_MATRIX_LST_H

#include "matrix_lst.h"

typedef struct s_m_node
{
	t_mtrx_lst		*matrix;
	int				type;
	struct s_m_node	*next;
	struct s_m_node	*prev;
}				t_mnode;

typedef struct s_matrix_matrix_lst
{
	t_mnode	*head;
	t_mnode	*last;
	int			size;
}				t_mtrx_mtrx;

typedef struct s_var_matrix_mlst
{
	t_mnode	*head;
	t_mnode *second;
	t_mnode *prev;
	t_mnode *next;
	t_mnode	*last;
	t_mnode	*second_last;
	t_mnode	*current;
	int		i;

}			t_var_m_mlst;

t_mtrx_mtrx	*ft_mtrx_mtrx_lst(void);
t_mnode		*init_matrix_node(void);
int			ft_create_node_matrix_add_front(t_mtrx_mtrx *lst_m , t_mtrx_lst *matrix);
int			ft_create_node_matrix_add_back(t_mtrx_mtrx *lst_m , t_mtrx_lst *matrix);
int			ft_remove_matrix_front(t_mtrx_mtrx *ma_lst);
int			ft_remove_matrix_back(t_mtrx_mtrx *ma_lst);
int			ft_remove_specific_matrix(t_mtrx_mtrx *m_matrix, t_mnode *matrix);
int			ft_delete_mtrx_mtrx_lst(t_mtrx_mtrx *m_matrix);


#endif