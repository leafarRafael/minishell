/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FUNCOES_TEMPORARIAS.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:26:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/27 09:54:38 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_str_type(int type);
void	print_all_type();

void	ft_print_array_lst(t_array_lst *lst, int front_back)
{
	int i;
	t_node_alst *temp;

	if (!lst)
		return ;
	if (!lst->head && !lst->last)
		return ;
	i = 0;
	if (front_back == 0)
		temp = lst->head;
	else
		temp = lst->last;
	while (i != lst->size)
	{
		printf("%c", temp->c);
		if (front_back == 0)
			temp = temp->next;
		else
			temp = temp->prev;
		i++;
	}
}

void	ft_print_array_lst_content_type(t_array_lst *lst)
{
	int i;
	t_node_alst *temp;

	if (!lst)
		return ;
	if (!lst->head && !lst->last)
		return ;
	i = 0;
	temp = lst->head;
	while (i != lst->size)
	{
		show_str_type(temp->type);
		printf("->[%c]->[%d]\n", temp->c, temp->type);
		temp = temp->next;
		i++;
	}
}

void	print_all_type()
{
	printf("\n%d NO_OPERATOR_TYPE \n", NO_OPERATOR_TYPE);
	printf("%d SINGLE_QUOTES\n", SINGLE_QUOTES);
	printf("%d DOUBLE_QUOTES\n", DOUBLE_QUOTES);
	printf("%d WHITE_SPACE\n", WHITE_SPACE);
	printf("%d DOLLAR_SING\n", DOLLAR_SIGN);
	printf("%d REDI_INFILE\n", REDI_INFILE);
	printf("%d REDIRECT\n", REDIRECT);
	printf("%d HERE_DOC\n", HERE_DOC);
	printf("%d APPEND\n", APPEND);
	printf("%d PIPE\n", PIPE);
	printf("%d AND\n", AND);
	printf("%d OR\n", OR);
	printf("%d LEFT_PAREN\n", LEFT_PAREN);
	printf("%d RIGHT_PAREN\n", RIGHT_PAREN);
}

void	show_str_type(int type)
{
	if (type == NO_OPERATOR_TYPE)
		printf("NO_OPERATOR_TYPE");
	if (type == SINGLE_QUOTES)
		printf("SINGLE_QUOTES");
	if (type == DOUBLE_QUOTES)
		printf("DOUBLE_QUOTES");
	if (type == WHITE_SPACE)
		printf("WHITE_SPACE");
	if (type == DOLLAR_SIGN)
		printf("DOLLAR_SING");
	if (type == REDI_INFILE)
		printf("REDI_INFILE");
	if (type == REDIRECT)
		printf("REDIRECT");
	if (type == HERE_DOC)
		printf("HERE_DOC");
	if (type == APPEND)
		printf("APPEND");
	if (type == PIPE)
		printf("PIPE");
	if (type == AND)
		printf("AND");
	if (type == OR)
		printf("OR");
	if (type == LEFT_PAREN)
		printf("LEFT_PAREN");
	if (type == RIGHT_PAREN)
		printf("RIGHT_PAREN");
}
