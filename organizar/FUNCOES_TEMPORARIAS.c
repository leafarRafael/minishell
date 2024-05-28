/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FUNCOES_TEMPORARIAS.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:26:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/28 19:53:46 by tforster         ###   ########.fr       */
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
		ft_putchar_fd(temp->c, STDERR_FILENO);
		if (front_back == 0)
			temp = temp->next;
		else
			temp = temp->prev;
		i++;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
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
	printf("%d REDI_OUT\n", REDI_OUT);
	printf("%d HERE_DOC\n", HERE_DOC);
	printf("%d APPEND\n", APPEND);
	printf("%d PIPE\n", PIPE);
	printf("%d AND_OP\n", AND_OP);
	printf("%d OR_OP\n", OR_OP);
	printf("%d OPEN_PAREN\n", OPEN_PAREN);
	printf("%d CLOSE_PAREN\n", CLOSE_PAREN);
}

// [COMMAND]
// printf("%s\033[1m\u279C  %sminishell ~:%s\033[0m", GRN, CYN, RST);
void	print_type(char *str, int len)
{
	printf(BLU "[");
	len--;
	len -= ft_strlen(str) - 1;
	printf(CYN "%s", str);
	printf(BLU "]");
	len--;
	while (len--)
	{
		printf(RST " ");
	}
}


void	show_str_type(int type)
{
	if (type == COMMAND)
		print_type("COMMAND", 13);
	if (type == META_LITERAL)
		print_type("META_LITERAL", 13);
	if (type == NO_OP_TYPE)
		print_type("NO_OP_TYPE", 13);
	if (type == S_QUOTES)
		print_type("S_QUOTES", 13);
	if (type == D_QUOTES)
		print_type("D_QUOTES", 13);
	if (type == WH_SPACE)
		print_type("WH_SPACE", 13);
	if (type == DOLLAR)
		print_type("DOLLAR_SING", 13);
	if (type == REDI_IN)
		print_type("REDI_IN", 13);
	if (type == REDI_OUT)
		print_type("REDI_OUT", 13);
	if (type == HERE_DOC)
		print_type("HERE_DOC", 13);
	if (type == APPEND)
		print_type("APPEND", 13);
	if (type == PIPE)
		print_type("PIPE", 13);
	if (type == AND_OP)
		print_type("AND_OP", 13);
	if (type == OR_OP)
		print_type("OR_OP", 13);
	if (type == OPEN_PAREN)
		print_type("OPEN_PAREN", 13);
	if (type == CLOSE_PAREN)
		print_type("CLOSE_PAREN", 13);
}

void	ft_print_matrix_line(t_mlst *m_line)
{
	t_lst_line *temp;
	int i;

	if (!m_line)
		printf("\nNULL\n");;
	if (!m_line->head)
		return ;
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

void ft_print_lst_matrix(t_mmlst *m_l)
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

void	ft_print_todos_os_tokens_expandidos(t_mmlst *mtrx_mtrx)
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
		if (is_operator(temp->type))
			printf("\n\n\n");
		if (is_operator(temp->next->type))
			printf("\n\n\n");
		ft_printf_matrix(matrix);
		ft_delete_cmatrix(matrix);
		temp = temp->next;
		i++;
	}
}

void ft_printtree(t_ast_n *root)
{
	if (root != NULL)
	{
		ft_print_matrix_line(root->m_lst->matrix);
		printf("=======================================\n");
		ft_printtree(root->left);
	}
}
