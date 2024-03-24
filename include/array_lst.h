/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_lst.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:47:19 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/24 18:08:18 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_LST_H
# define ARRAY_LST_H

#include <stdlib.h>

typedef struct s_node_array_list
{
	char						c;
	int							type;
	struct s_node_array_list	*next;
	struct s_node_array_list	*prev;
}           t_node_alst;

typedef struct s_array_list
{
	t_node_alst *head;
	t_node_alst *last;
	int         size;
}           t_array_lst;

typedef struct s_matrix_list
{
	t_node_alst			*head;
	t_node_alst			*last;
	t_array_lst			*head_line;
	t_array_lst			*next_line;
	t_array_lst			*prev_line;
	t_array_lst			*last_line;
	int         size;
}           t_matrix_lst;

typedef struct s_var_array_list
{
	t_node_alst	*current_node;
	t_node_alst	*next_node;
	t_node_alst	*prev_node;
	t_node_alst *temp_node;
	t_node_alst *head;
	t_node_alst *last;
	t_node_alst *second;
	t_node_alst	*second_last;
	int			i;
}			t_var;

t_array_lst		*init_array_lst(void);
t_matrix_lst	*ft_init_matrix_lst(void);
int				ft_create_addnode_back_alst(t_array_lst *lst, char content);
int				ft_addnode_back(t_array_lst *lst, t_node_alst *node);
int				ft_create_addnode_front_alst(t_array_lst *lst, char content);
int				ft_addnode_front(t_array_lst *lst, t_node_alst *node);;
int				ft_remove_node_front(t_array_lst *lst);
int				ft_remove_node_back(t_array_lst *lst);
int				ft_remove_specific_node(t_array_lst *lst, t_node_alst *node);
int				ft_remove_specific_content(t_array_lst *lst, char c);
int				ft_delete_list(t_array_lst *lst);


#endif