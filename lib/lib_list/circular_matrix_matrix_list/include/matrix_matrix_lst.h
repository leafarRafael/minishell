/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_matrix_lst.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:46:47 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/18 10:01:26 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_MATRIX_LST_H
# define MATRIX_MATRIX_LST_H
# include "matrix_lst.h"

typedef struct s_m_node
{
	t_mlst		*matrix;
	int			type;
	int			in_parent;
	int			in_tree;
	struct s_m_node	*next;
	struct s_m_node	*prev;
}				t_mnode;

typedef struct s_matrix_matrix_lst
{
	t_mnode	*head;
	t_mnode	*last;
	int		size;
}				t_mmlst;

typedef struct s_var_matrix_mlst
{
	t_mnode	*head;
	t_mnode	*second;
	t_mnode	*prev;
	t_mnode	*next;
	t_mnode	*last;
	t_mnode	*second_last;
	t_mnode	*current;
	int		i;
}			t_var_m_mlst;


t_mmlst	*init_mmlst(void);
t_mnode	*init_matrix_node(void);
int		ft_mmlst_add_front(t_mmlst *lst_m, t_mlst *matrix);
int			ft_mmlst_add_back(t_mmlst *lst_m, t_mlst *matrix);
int			ft_remove_matrix_front(t_mmlst *ma_lst);
int			ft_remove_matrix_back(t_mmlst *ma_lst);
int			ft_remove_specific_matrix(t_mmlst *m_matrix, t_mnode *matrix);
int			ft_delete_mmlst(t_mmlst *m_matrix);

#endif