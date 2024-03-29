/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/29 10:49:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

void	print_operator(t_lst *lst);
int		ft_have_operator(t_lst *lst);
int		ft_chage_pointer(t_node **current_node, t_node *ref_node, int *is_aspa);

int main()
{
	t_var_minishell var;
	t_lst			*lst_array;
	t_matrix_lst	*matrix_lst;

	matrix_lst = ft_init_matrix();
	lst_array = ft_init_lst();
	var.infile = readline("minishell ~:"); // n 0
	ft_add_string_in_list(lst_array, var.infile); // n 1
	ft_scanner_input(lst_array); // n 2
	

	if (ft_have_operator(lst_array))// n 3
	{// n 3.1
		printf("\npossui operador\n");
	}
	else
	{ // n 3.2
		printf("\nnão possui operador\n");
	}
	print_operator(lst_array);
	ft_delete_list(lst_array);
	free(var.infile);
}

void	print_operator(t_lst *lst)
{
	t_var	var;
	int		is_aspa;

	is_aspa = 0;
	var.current_node = lst->head;
	while (lst->size >= 0)
	{
		//if (var.current_node->type == WHITE_SPACE && is_aspa == 0)
			//if (ft_chage_pointer(&var.current_node, lst->head, &is_aspa))
				//break ;
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

int	ft_chage_pointer(t_node **current_node, t_node *ref_node, int *is_aspa)
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