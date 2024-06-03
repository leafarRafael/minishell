/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:50:52 by tforster          #+#    #+#             */
/*   Updated: 2024/06/03 17:38:40 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_parser.h"

int	parse_out_prnht(char *str, t_parse **parse, int *index)
{
	int	status;

	status = NO_ERROR;
	while (str[*index])
	{
		if (th_is_tab(str[*index]))
			(*index)++;
		else if (str[*index] == ')')
			status = syntax_error(*parse, str, N_OPN_PRNTH);
		else if (str[*index] == '(')
			status = parse_bfr_fst_prnth(parse, str, index);
		else if (th_is_quote(str, *index))
			status = parse_quote(str, parse, index);
		else if (th_is_logical_oprtr(str, *index))
			status = parse_oprtr(str, parse, index);
		else if (th_is_io_rdrct(str, *index))
			status = parse_rdrct(str, parse, index);
		else
			status = parse_text(str, parse, index);
		if (*parse && tkn_is_oprtr(*parse))
			status = syntax_error(*parse, str, TKN_AFT_OPN_PRNTH);
		if (status > 0)
			break ;
	}
	return (status);
}

int	parse_prnth(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		status;

	status = NO_ERROR;
	ptr = parse_add_back(parse, parse_init(OPEN_PAREN, *index + 1));
	while (!status && str[(*index)++])
	{
		if (th_is_tab(str[*index]))
			ptr->size++;
		else if (str[*index] == '(')
			status = parse_bfr_sub_prnth(ptr, str, index);
		else if (str[*index] == '\0')
			return (syntax_error(*parse, str, N_CLS_PRNTH));
		else if (str[*index] == ')')
			return (parse_bfr_cls_prnth(ptr, str, index));
		else if (th_is_quote(str, *index))
			status = append_sub(str, ptr, index, parse_quote);
		else if (th_is_logical_oprtr(str, *index))
			status = append_sub(str, ptr, index, parse_oprtr);
		else if (th_is_io_rdrct(str, *index))
			status = append_sub(str, ptr, index, parse_rdrct);
		else
			status = append_sub(str, ptr, index, parse_text);
	}
	return (status);
}
