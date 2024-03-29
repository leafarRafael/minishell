/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:02:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/29 17:18:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_operator(int type)
{
	return (type & (REDI_INFILE | REDIRECT | HERE_DOC | APPEND | PIPE | AND | OR | LEFT_PAREN | RIGHT_PAREN));
}

int		is_operator_composite(int c_type, int n_type)
{
	return ((c_type && n_type) & (HERE_DOC | APPEND | PIPE | AND | OR));
}