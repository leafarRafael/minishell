/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/29 18:04:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

int main()
{
	t_var_minishell var;
	t_lst			*input_user;
	t_matrix_lst	*matrix_lst;

	matrix_lst = ft_init_matrix();
	input_user = ft_init_lst();
	var.infile = readline("minishell ~:"); // n 0
	ft_add_string_in_list(input_user, var.infile); // n 1
	ft_scanner_input(input_user); // n 2
	if (ft_have_operator(input_user))// n 3
	{// n 3.1
		printf("\npossui operador\n");
	}
	else
	{ // n 3.2
		printf("\nnão possui operador\n");
	}
	ft_separate_operators(matrix_lst, input_user);
	ft_print_matrix_line(matrix_lst);
	// print_operator(input_user);
	// ft_delete_list(input_user);
	// free(var.infile);
}

































// n 0 = receber string do utilizador;
// n 1 = etapa 1 = copiar string para uma lista de caracters
// n 2 = etapa 2 = scanear a lista e indentificar caracteres "normais" operadores e delimitadores (definido por type)

/*
	n 3 = etapa 3 = verificar se existe algum operador

	n 3.1 = { caso possua operador, sera criado uma matrix de listas, onde cada lista representara o conteudo 
	anteriores ao operador, uma lista para o conteudo do operador, e uma lista para os dados apos o operador
	caso existam mais de 1 operadores seram criadas listas seguindo esta logica }

	// n 3.2 = caso nao possua operador passar a lista envia a primeira lista para tokenização e verificaçã de expansao
*/