/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 14:46:02 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	t_array_lst *lst_array;
	t_var_minishell var;

	lst_array = init_array_lst();
	var.infile = readline("minishell ~:");
	var.i = 0;
	while (var.infile[var.i])
	{
		if (ft_create_addnode_back_alst(lst_array, var.infile[var.i]))
		{
			printf("error creation array_list");
			exit(-1);
		}
		var.i++;
	}
	ft_print_array_lst(lst_array, 1);
	ft_delete_list(lst_array);
	free(var.infile);
}
