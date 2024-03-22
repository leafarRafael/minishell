/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:48:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 14:31:07 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISEHLL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "ft_printf.h"
# include "libft.h"
# include "string.h"
# include "key_words.h"
# include "array_lst.h"
# include "binary_tree.h"

typedef struct s_variables_minishell
{
	char	*infile;
	int		i;
}			t_var_minishell;


void	ft_print_array_lst(t_array_lst *lst, int front_back);

#endif