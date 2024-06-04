/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:02:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:53:07 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_composite(int c_type, int n_type)
{
	return ((c_type && n_type) & (HERE_DOC | APPEND | PIPE | AND_OP | OR_OP));
}

int	is_operator(int type)
{
	return (type & (PIPE | AND_OP | OR_OP));
}

int	is_operator_redirect(int type)
{
	return (type & (REDI_IN | REDI_OUT | HERE_DOC | APPEND));
}

int	ft_hdoc_limiter(int type)
{
	return (type &(OPEN_PAREN | CLOSE_PAREN | PIPE | AND_OP | OR_OP
			| REDI_IN | REDI_OUT | HERE_DOC | APPEND | WH_SPACE));
}

int	is_wildcard(int type)
{
	return (type == WILDCARD);
}
