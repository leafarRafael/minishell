/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FUNCOES_TEMPORARIAS.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:26:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/16 16:02:14 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_str_type(int type);
void	print_all_type();
static int	ft_chage_pointer(t_node **current_node, t_node *ref_node, int *is_aspa);


void	ft_printf_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

void	ft_print_array_lst(t_lst *lst, int front_back)
{
	int i;
	t_node *temp;

	if (!lst)
		return ;
	if (!lst->head && !lst->last)
		return ;
	i = 1;
	if (front_back == 0)
		temp = lst->head;
	else
		temp = lst->last;
	while (i <= lst->size)
	{
		printf("%c", temp->c);
		if (front_back == 0)
			temp = temp->next;
		else
			temp = temp->prev;
		i++;
	}
}

void	ft_print_array_lst_content_type(t_lst *lst)
{
	int i;
	t_node *temp;

	if (!lst)
		return ;
	if (!lst->head && !lst->last)
		return ;
	i = 0;
	temp = lst->head;
	while (i != lst->size)
	{
		show_str_type(temp->type);
		printf(" [%c] [%d] [%d] [priority = %d] \n", temp->c, temp->type, temp->paren, temp->priority);
		temp = temp->next;
		i++;
	}
}

void	print_all_type()
{
	printf("\n%d NO_OP_TYPE \n", NO_OP_TYPE);
	printf("%d S_QUOTES\n", S_QUOTES);
	printf("%d D_QUOTES\n", D_QUOTES);
	printf("%d WH_SPACE\n", WH_SPACE);
	printf("%d DOLLAR_SING\n", DOLLAR);
	printf("%d REDI_IN\n", REDI_IN);
	printf("%d REDIRECT\n", REDIRECT);
	printf("%d HERE_DOC\n", HERE_DOC);
	printf("%d APPEND\n", APPEND);
	printf("%d PIPE\n", PIPE);
	printf("%d AND_OP\n", AND_OP);
	printf("%d OR_OP\n", OR_OP);
	printf("%d OPEN_PAREN\n", OPEN_PAREN);
	printf("%d CLOSE_PAREN\n", CLOSE_PAREN);
}

void	show_str_type(int type)
{
	if (type == META_LITERAL)
		printf("META_LITERAL");
	if (type == NO_OP_TYPE)
		printf("NO_OP_TYPE");
	if (type == S_QUOTES)
		printf("S_QUOTES");
	if (type == D_QUOTES)
		printf("D_QUOTES");
	if (type == WH_SPACE)
		printf("WH_SPACE");
	if (type == DOLLAR)
		printf("DOLLAR_SING");
	if (type == REDI_IN)
		printf("REDI_IN");
	if (type == REDIRECT)
		printf("REDIRECT");
	if (type == HERE_DOC)
		printf("HERE_DOC");
	if (type == APPEND)
		printf("APPEND");
	if (type == PIPE)
		printf("PIPE");
	if (type == AND_OP)
		printf("AND_OP");
	if (type == OR_OP)
		printf("OR_OP");
	if (type == OPEN_PAREN)
		printf("OPEN_PAREN");
	if (type == CLOSE_PAREN)
		printf("CLOSE_PAREN");
}

void	ft_print_matrix_line(t_mtrx_lst *m_line)
{
	t_lst_line *temp;
	int i;

	i = 1;
	temp = m_line->head;
	while (i <= m_line->size)
	{
		ft_print_array_lst(temp->lst, 0);
		printf("\n");
		i++;
		temp = temp->next;
	}
}

void	print_operator(t_lst *lst)
{
	t_var	var;
	int		is_aspa;

	is_aspa = 0;
	var.current_node = lst->head;
	while (lst->size >= 0)
	{
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

static int	ft_chage_pointer(t_node **current_node, t_node *ref_node, int *is_aspa)
{
	*current_node = (*current_node)->next;
	if ((*current_node)->type & (D_QUOTES | S_QUOTES))
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

void ft_print_lst_matrix(t_mtrx_mtrx *m_l)
{
	t_mnode	*temp;
	int 	i;

	if (m_l == NULL)
		return ;
	if (m_l->size == 0)
		return ;
	i = 1;
	temp = m_l->head;
	while (i <= m_l->size)
	{
		printf("\npriority = %d\n", temp->type);
		ft_print_matrix_line(temp->matrix);
		temp = temp->next;
		i++;
	}
}

void	ft_print_todos_os_tokens_expandidos(t_mtrx_mtrx *mtrx_mtrx)
{
	t_mnode		*temp;
	char		**matrix;
	int			i;

	i = 1;
	temp = mtrx_mtrx->head;
	matrix = NULL;
	while (i <= mtrx_mtrx->size)
	{
		matrix = ft_expand_m_lst_to_cmtrx(temp->matrix);
		if (matrix == NULL)
			ft_remove_specific_matrix(mtrx_mtrx, temp);
		ft_printf_matrix(matrix);
		ft_delete_cmatrix(matrix);
		temp = temp->next;
		i++;
	}
}