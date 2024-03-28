/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:48:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/28 08:36:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "get_next_line.h"
# include "matrix_lst.h"

typedef struct s_variables_minishell
{
	char	*infile;
	int		i;
}			t_var_minishell;

/*
			Function parse
*/
void		ft_scanner_input(t_lst *lst);

void	ft_print_array_lst(t_lst *lst, int front_back);
void	ft_print_array_lst_content_type(t_lst *lst);
void	show_str_type(int type);
void	print_all_type();


#endif