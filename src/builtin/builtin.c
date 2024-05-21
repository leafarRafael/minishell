/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:50:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/21 17:54:15 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

static int	ft_builtin_type(char *str, int len);

int	is_in_set(char ch, char *set)
{
	while (*set)
	{
		if (ch == *(set++))
			return (1);
	}
	return (0);
}

int	ft_valid_builtin(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	int		len;
	int		buitlin;
	char	*str;

	// ft_putstr_fd("FUNCTION TO CHECK IF BUILT_IN\n", 2);
	// ft_print_array_lst(cmd->m_lst->matrix->head->lst);
	// ft_print_array_lst(cmd->m_lst->matrix->head->next->lst);

	var->env = ft_path_env(mini->m_lst_env);
	var->command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);

	len = cmd->m_lst->matrix->head->lst->size;
	str = var->command_m[0];
	// var->path_exe = ft_get_executable(mini, var, ast);

	// ft_putstr_fd("THE BUILTIN TO BE CHECK: [", 2);
	// ft_putstr_fd(str, 2);
	// ft_putstr_fd("] SIZE = ", 2);
	// ft_putnbr_fd(len, 2);

	buitlin = ft_builtin_type(str, len);
	// free(var->command_m);
	// ft_delete_matrix()
	return (buitlin);
}

static int	ft_builtin_type(char *ch, int len)
{
	int	bltn;

	bltn = 0;
	if (len == 2)
		bltn += (*ch == 'c') * (*(ch + 1) == 'd') * CD;
	else if (len == 3)
		bltn += (*ch == 'e') * (*(ch + 1) == 'n') * (*(ch + 2) == 'v') * ENV
			+ (*ch == 'p') * (*(ch + 1) == 'w') * (*(ch + 2) == 'd') * PWD;
	else if (len == 4)
		bltn += (*ch == 'e') * (*(ch + 1) == 'c') * (*(ch + 2) == 'h')
			* (*(ch + 3) == 'o') * ECHO
			+ (*ch == 'e') * (*(ch + 1) == 'x') * (*(ch + 2) == 'i')
			* (*(ch + 3) == 't') * EXIT;
	else if (len == 5)
		bltn += (*ch == 'u') * (*(ch + 1) == 'n') * (*(ch + 2) == 's')
			* (*(ch + 3) == 'e') * (*(ch + 4) == 't') * UNSET;
	else if (len == 6)
		bltn += (*ch == 'e') * (*(ch + 1) == 'x')
			* (*(ch + 2) == 'p') * (*(ch + 3) == 'o')
			* (*(ch + 4) == 'r') * (*(ch + 5) == 't') * EXPORT;
	// ft_putstr_fd("\nTHE RESULT IS [", 2);
	// ft_putnbr_fd(bltn, 2);
	// ft_putstr_fd("]\nEND\n", 2);
	return (bltn);
}

/*
cd		2
env		3
pwd		3
echo	4
exit	4
unset	5
export	6
*/
