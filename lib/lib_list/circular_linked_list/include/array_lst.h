/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_lst.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:47:19 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/15 09:23:20 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_LST_H
# define ARRAY_LST_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char			c;
	int				type;
	int				paren;
	int				priority;
	struct s_node	*next;
	struct s_node	*prev;
}			t_node;

typedef struct s_lst
{
	t_node		*head;
	t_node		*last;
	int			size;
}			t_lst;

typedef struct s_var_array_list
{
	t_node	*current_node;
	t_node	*next_node;
	t_node	*prev_node;
	t_node	*temp_node;
	t_node	*head;
	t_node	*last;
	t_node	*second;
	t_node	*second_last;
	int			i;
}			t_var;

t_lst			*ft_init_lst(void);
int				ft_create_node_add_back(t_lst *lst, char content);
int				ft_add_node_back(t_lst *lst, t_node *node);
int				ft_create_add_node_front(t_lst *lst, char content);
int				ft_add_node_front(t_lst *lst, t_node *node);;
int				ft_remove_node_front(t_lst *lst);
int				ft_remove_node_back(t_lst *lst);
int				ft_remove_specific_node(t_lst *lst, t_node *node);
int				ft_remove_specific_content(t_lst *lst, char c);
int				ft_delete_list(t_lst *lst);
int				ft_add_string_in_list(t_lst *lst, char *array);
t_node			*ft_remove_return_node(t_lst *lst, t_node *node);
int				ft_insert_lst_between_lst(t_lst *lst_dest, t_node *between_a, t_node *between_b, t_lst *lst_new);
char			*ft_cpy_lst_to_array(t_lst *lst);


#endif