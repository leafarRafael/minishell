/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_error_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:19:53 by tforster          #+#    #+#             */
/*   Updated: 2024/06/03 18:36:39 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"

char	*error_opn_prnth(t_sytx_er error)
{
	if (error == TKN_BFR_OPN_PRNTH)
		return (")");
	else
		return ("(");
}

char	*error_name(t_parse *parse, char *str, t_sytx_er error, int *flag)
{
	int		index;
	char	*token;

	if (error == TKN_AFT_CLS_PRNTH)
		return (")");
	if (error == TKN_BFR_OPN_PRNTH)
	{
		index = 0;
		token = malloc((parse->size + 1) * sizeof(char));
		while (index < parse->size)
		{
			token[index] = str[parse->start + index];
			index++;
		}
		token[index] = '\0';
		*flag = 1;
		return (token);
	}
	return (NULL);
}
