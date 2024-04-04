/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:02:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 08:40:47 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_operator(int type)
{
	return (type & (REDI_INFILE | REDIRECT | HERE_DOC | APPEND | PIPE | AND | OR));
}

int		is_operator_composite(int c_type, int n_type)
{
	return ((c_type && n_type) & (HERE_DOC | APPEND | PIPE | AND | OR));
}