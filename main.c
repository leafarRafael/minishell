/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/10 17:12:54 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

int main()
{
	t_var_minishell v;
	t_mtrx_lst		*a;
	t_mtrx_lst		*b;
	t_mtrx_lst		*c;

	v.input_user = ft_init_lst();
	v.infile = readline("minishell ~:");
	ft_add_string_in_list(v.input_user, v.infile);
	ft_scanner_input(v.input_user);
	if (!ft_have_operator(v.input_user))
	{
		v.matrix_lst = ft_simple_comand(v.input_user);
		ft_print_matrix_line(v.matrix_lst);
	}
	else
	{
		v.list_matrix = ft_mtrx_mtrx_lst();
		while (v.input_user->size > 0)
			ft_create_node_matrix_add_back(v.list_matrix, ft_simple_comand(v.input_user));
		ft_remove_first_matrix(v.list_matrix);
		ft_remove_first_matrix(v.list_matrix);
		ft_remove_first_matrix(v.list_matrix);
		free(v.input_user);
		free(v.infile);
		free(v.list_matrix);

		//ft_print_lst_matrix(v.list_matrix);
	}
	
}
