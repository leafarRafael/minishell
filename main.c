/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/30 15:47:38 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

t_node	*ask_to_expansion(t_matrix_lst *m_lst);
t_node	*ask_expansion(t_matrix_lst *m_lst);
void	ft_printf_matrix();
char	*ft_expand(t_node *node, t_node *l_node);

int main()
{
	t_var_minishell var;
	t_lst			*input_user;
	t_matrix_lst	*matrix_lst;
	t_node			*i_node;
	t_node			*l_node;

	//ft_printf_matrix();
	matrix_lst = ft_init_matrix();
	input_user = ft_init_lst();
	var.infile = readline("minishell ~:"); // n 0
	ft_add_string_in_list(input_user, var.infile); // n 1
	ft_scanner_input(input_user); // n 2
	if (ft_have_operator(input_user))// n 3
	{// n 3.1

	}
	else
	{ // n 3.2

	}
	ft_separate_operators(matrix_lst, input_user);
	i_node = ask_to_expansion(matrix_lst);
	l_node = ask_expansion(matrix_lst);
	printf("\n[[[[[%c]]]]]\n", i_node->c);
	printf ("\n\n[%s]\n\n\n", getenv(ft_expand(i_node, l_node)));
	ft_print_matrix_line(matrix_lst);
	// print_operator(input_user);
	// ft_delete_list(input_user);
	// free(var.infile);
}

void	ft_printf_matrix()
{
	int	i;

	i = 0;
	while (__environ[i])
	{
		printf("%s\n", __environ[i]);
		i++;
	}
}


t_node	*ask_to_expansion(t_matrix_lst *m_lst)
{
	int			i;
	int			j;
	t_lst_line *t_line;
	t_lst		*lst_current;
	t_node		*node;

	t_line = m_lst->head;
	lst_current = t_line->lst;
	i = 1;
	while (i <= m_lst->size)
	{
		j = 1;
		node = lst_current->head;
		while (j <= lst_current->size)
		{
			if (node->c == '$')
				return (node);
			node = node->next;
			j++;
		}
		t_line = t_line->next;
		lst_current = t_line->lst;
		i++;
	}
	return (NULL);
}


t_node	*ask_expansion(t_matrix_lst *m_lst)
{
	int			i;
	int			j;
	t_lst_line *t_line;
	t_lst		*lst_current;
	t_node		*node;

	t_line = m_lst->head;
	lst_current = t_line->lst;
	i = 1;
	while (i <= m_lst->size)
	{
		j = 1;
		node = lst_current->head;
		while (j <= lst_current->size)
		{
			if (node->c == '$')
			{
				node = node->next;
				while (node->type == NO_OPERATOR_TYPE)
				{
					printf("%c", node->c);
					node = node->next;
				}
				return (node);
			}
			node = node->next;
			j++;
		}
		t_line = t_line->next;
		lst_current = t_line->lst;
		i++;
	}
	return (NULL);
}

char	*ft_expand(t_node *node, t_node *l_node)
{
	int	i;
	t_node *current;
	char	*variable;

	current = node->next;
	i = 1;
	while (current != l_node)
	{
		current = current->next;
		i++;
	}
	variable = ft_calloc(sizeof(char ), (i +1));
	i = 0;
	node = node->next;
	while (node != l_node)
	{
		variable[i] = node->c;
		node = node->next;
		i++;
	}
	return (variable);
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