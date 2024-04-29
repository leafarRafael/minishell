/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:02:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:41:39 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_composite(int c_type, int n_type)
{
	return ((c_type && n_type) & (HERE_DOC | APPEND | PIPE | AND_OP | OR_OP));
}

int	is_operator(int type)
{
	return (type & (PIPE | AND_OP | OR_OP | OPEN_PAREN | CLOSE_PAREN));
}

/* 
int		is_operator(int type)
{
	return (type & (REDI_IN | REDI_OUT 
		| HERE_DOC | APPEND | PIPE | AND_OP 
		| OR_OP | OPEN_PAREN | CLOSE_PAREN));
} */