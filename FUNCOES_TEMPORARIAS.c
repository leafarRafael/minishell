/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FUNCOES_TEMPORARIAS.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:26:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/24 11:56:31 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_ttypee(int type);

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
		printf_ttypee(temp->type);
		printf("->[%c]->[%d]\n", temp->c, temp->type);
		temp = temp->next;
		i++;
	}
}

void	printf_ttypee(int type)
{
	if (type == NO_OPERATOR_TYPE)
		printf("NO_OPERATOR_TYPE");
	if (type == SINGLE_QUOTES)
		printf("SINGLE_QUOTES");
	if (type == DOUBLE_QUOTES)
		printf("DOUBLE_QUOTES");
	if (type == WHITE_SPACE)
		printf("WHITE_SPACE");
	if (type == DOLLAR_SING)
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