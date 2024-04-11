/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:35:17 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/11 16:27:56 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "array_lst.h"
# include "key_words.h"

typedef enum s_priority
{
    LOWEST = 0,
    LOW = 1 << 0,
    MEDIUM = 1 << 1,
    HIGH = 1 << 2,
	HERE = HERE_DOC
}		t_priority;

typedef struct s_scanner
{
	t_node	*node;
	int		parentheses;
	int		i;
	int		type;
	int		s_quotes;
	int		d_quotes;
	
}		t_scan;

void	ft_scanner_parenthes(t_lst *lst);
void	ft_scanner_quotes(t_lst *lst);
void	ft_scanner_simple_operator(t_lst *lst);
void	ft_scanner_composite(t_lst *lst);
void	ft_scanner_input(t_lst *lst);
void	ft_scanner_priority_type(t_lst *lst);

#endif