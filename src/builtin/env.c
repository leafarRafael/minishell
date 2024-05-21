/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:03:19 by tforster          #+#    #+#             */
/*   Updated: 2024/05/21 17:36:49 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_env(t_mini *mini)
{
	ft_printf_matrix(mini->env);
}

void	ft_print_array_lst(t_lst *lst)
{
	int i;
	t_node *temp;

	if (!lst)
		return ;
	if (!lst->head && !lst->last)
		return ;
	i = 1;
	temp = lst->head;
	while (i <= lst->size)
	{
		ft_putchar_fd(temp->c, STDERR_FILENO);
		temp = temp->next;
		i++;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	ft_print_matrix_line(t_mlst *m_line)
{
	t_llst *temp;
	int i;

	if (!m_line)
		printf("\nNULL\n");;
	if (!m_line->head)
		return ;
	i = 1;
	temp = m_line->head;
	while (i <= m_line->size)
	{
		ft_print_array_lst(temp->lst);
		// ft_putstr_fd("\n", 2);
		i++;
		temp = temp->next;
	}
}
