/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:44:47 by tforster          #+#    #+#             */
/*   Updated: 2024/06/10 14:21:36 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_utils.h"

void	init_minishell(t_mini *mini)
{
	mini->mmlst = NULL;
	mini->input_lst = NULL;
	mini->input = NULL;
	mini->env = NULL;
	mini->temp_environ = NULL;
	mini->m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	mini->color = ft_init_color();
	mini->collect = ft_init_collector();
	mini->collect_ast = ft_init_collector();
	mini->status = 0;
	mini->i_color = 1;
	swap_tty(COPY, mini);
}

void	print_pwd(void)
{
	char	*name;

	name = NULL;
	name = ft_get_program_name();
	if (name)
	{
		ft_putstr_fd(name, 2);
		free(name);
	}
}

char	*sig_eof(char *str)
{
	if (str)
		free(str);
	str = malloc(sizeof(char) * 5);
	str[0] = 'e';
	str[1] = 'x';
	str[2] = 'i';
	str[3] = 't';
	str[4] = '\0';
	return (str);
}
