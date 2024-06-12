/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/06/12 16:56:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_parser.h"
#include "th_syntax.h"

int	last_tkn(char *str, t_parse *parse, int status)
{
	t_parse		*last;

	last = parse_last(parse);
	if (!status && parse && (tkn_is_oprtr(last) || tkn_is_rdrct(last)))
		return (syntax_error(last, str, TKN_BFR_CLS_PRNTH));
	return (status);
}

int	th_parse_param(char *str)
{
	t_parse	*parse;
	int		index;
	int		status;

	parse = NULL;
	index = 0;
	status = parse_out_prnht(str, &parse, &index);
	status = last_tkn(str, parse, status);
	if (parse)
		parse_free(parse);
	else
		return (1);
	if (status)
		return (1);
	return (0);
}
