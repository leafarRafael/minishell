/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/27 18:49:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>


void	print_operator(t_array_lst *lst);
int		ft_chage_pointer(t_node_alst **current_node, t_node_alst *ref_node, int *is_aspa);
void	ft_add_list_to_matrix(t_matrix *matrix, t_array_lst *lst);
void	print_matrix(t_matrix *matrix);

int main()
{
	t_array_lst		*lst_array;
	t_var_minishell var;
	t_matrix		*matrix;

	matrix = ft_init_matrix();
	lst_array = init_array_lst();
	var.infile = readline("minishell ~:");
	ft_add_string_in_list(lst_array, var.infile);
	ft_add_list_to_matrix(matrix, lst_array);
	ft_scanner_input(lst_array);
	print_matrix(matrix);
	print_operator(lst_array);
	ft_delete_list(lst_array);
	free(var.infile);
	free(matrix);
}

void	print_operator(t_array_lst *lst)
{
	t_var	var;
	int		is_aspa;

	is_aspa = 0;
	var.current_node = lst->head;
	while (1)
	{
		if (var.current_node->type == WHITE_SPACE && is_aspa == 0)
			if (ft_chage_pointer(&var.current_node, lst->head, &is_aspa))
				break ;
		if (is_operator(var.current_node->type))
		{
			printf("\n");
			if (var.current_node->type == var.current_node->next->type && var.current_node->next != lst->head)
			{
				printf("%c", var.current_node->c);
				if (ft_chage_pointer(&var.current_node, lst->head, &is_aspa))
					break ;
			}
			printf("%c\n", var.current_node->c);
		}
		else
			printf("%c", var.current_node->c);
		if (ft_chage_pointer(&var.current_node, lst->head, &is_aspa))
			break ;
	}
}

int	ft_chage_pointer(t_node_alst **current_node, t_node_alst *ref_node, int *is_aspa)
{
	*current_node = (*current_node)->next;
	if ((*current_node)->type & (DOUBLE_QUOTES | SINGLE_QUOTES))
	{
		if ((*is_aspa) == 0)
			(*is_aspa)++;
		else
			(*is_aspa)--;
	}
	if ((*current_node) == ref_node)
		return (-1) ;
	return (0);
}

// void ft_add_list_to_matrix(t_matrix *matrix, t_node_alst *node)
// {
// 	t_array_lst	*list;

// 	list = malloc(sizeof(t_array_lst));
// 	if (!list)
// 		return ;
// 	if (!matrix)
// 		return ;
// 	ft_addnode_back(list, node);
// 	matrix->list = list;
// 	matrix->next = NULL;
// 	matrix->prev = NULL;
// 	matrix->size = 0;
// }

void ft_add_list_to_matrix(t_matrix *matrix, t_array_lst *lst)
{
	matrix->list = lst;
	matrix->next = NULL;
	matrix->prev = NULL;
	matrix->size = 0;
}

void	print_matrix(t_matrix *matrix)
{
	ft_print_array_lst_content_type(matrix->list);
}