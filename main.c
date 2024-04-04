/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 16:59:47 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

int	ft_valid_subshell(t_lst *lst);
int	ft_is_subshell(char *input);

int main()
{
	t_var_minishell var;

	var.matrix_lst = ft_init_matrix();
	var.input_user = ft_init_lst();
	var.infile = readline("minishell ~:");
	ft_add_string_in_list(var.input_user, var.infile);
	ft_scanner_input(var.input_user);
	ft_print_array_lst_content_type(var.input_user);
	printf("\n");
	if (ft_valid_subshell(var.input_user))
	{
		printf("sintaxe error\n");
		exit(1);	
	}
	if (ft_have_operator(var.input_user))
	{
		if (ft_separate_operators(var.matrix_lst, var.input_user))
			printf("aqui um erro");
	}
	else
		ft_add_list_front(var.matrix_lst, var.input_user);
	ft_expander_variable(var.matrix_lst);
	ft_print_matrix_line(var.matrix_lst);
}

int	ft_valid_subshell(t_lst *lst)
{
	t_var	var;
	int		left_paren;
	int		right_paren;

	left_paren = 0;
	right_paren = 0;
	var.head = lst->head;
	var.i = 1;
	while (var.i <= lst->size)
	{
		if(left_paren == 0 && right_paren != 0)
			return (-1);
		if (right_paren > left_paren)
			return (-1);
		if (var.head->type == OPEN_PAREN)
			left_paren++;
		if (var.head->type == CLOSE_PAREN)
			right_paren++;
		var.i++;
		var.head = var.head->next;			
	}
	if (left_paren != right_paren)
		return (-1);
	return (0);
}
