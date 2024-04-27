/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_type_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:03:16 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/27 16:10:44 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_words.h"

int	is_simple_type(char current_c)
{
	if (ft_s_quotes(current_c))
		return (S_QUOTES);
	if (ft_d_quotes(current_c))
		return (D_QUOTES);
	if (ft_dollar(current_c))
		return (DOLLAR);
	if (ft_infile(current_c))
		return (REDI_IN);
	if (ft_outfile(current_c))
		return (REDI_OUT);
	if (ft_open_parent(current_c))
		return (OPEN_PAREN);
	if (ft_close_parent(current_c))
		return (CLOSE_PAREN);
	if (is_pipe(current_c))
		return (PIPE);
	if (ft_space(current_c))
		return (WH_SPACE);
	if (ft_tab(current_c))
		return (WH_SPACE);
	return (NO_OP_TYPE);
}

int	ft_is_composite_type(char current_c, char next_c)
{
	if (ft_heredoc(current_c, next_c))
		return (HERE_DOC);
	if (ft_append(current_c, next_c))
		return (APPEND);
	if (ft_and_op(current_c, next_c))
		return (AND_OP);
	if (ft_or_op(current_c, next_c))
		return (OR_OP);
	return (-1);
}
