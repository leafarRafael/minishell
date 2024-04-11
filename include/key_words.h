/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_words.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:46:51 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/11 11:53:33 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_WORDS_H
# define KEY_WORDS_H

typedef enum s_type_character
{
	NO_OP_TYPE  = 0,
	S_QUOTES = 1 << 0,
	D_QUOTES = 1 << 1,
	WH_SPACE  = 1 << 2,
	DOLLAR = 1 << 3,
	REDI_IN = 1 << 4,
	REDIRECT = 1 << 5,
	HERE_DOC = 1 << 6,
	APPEND = 1 << 7,
	PIPE = 1 << 8,
	AND_OP = 1 << 9,
	OR_OP = 1 << 10,
	OPEN_PAREN = 1 << 11,
	CLOSE_PAREN = 1 << 12,
	META_LITERAL = 1 << 13,
	COMMAND = 1 << 14,
	END_OF = 1 << 15
}       t_type_character;

int	ft_or_op(char current, char next);
int	ft_and_op(char current, char next);
int	is_pipe(char c);
int	is_operator(int type);
int	is_operator_composite(int c_type, int n_type);
int	ft_heredoc(char current, char next);
int	ft_append(char current, char next);
int	ft_infile(char current);
int	ft_outfile(char current);
int	ft_d_quotes(char current);
int	ft_s_quotes(char current);
int	ft_space(char current);
int	ft_tab(char current);
int	ft_dollar(char current);
int	ft_open_parent(char c);
int	ft_close_parent(char c);
int	is_simple_type(char current_c);
int	ft_is_composite_type(char current_c, char next_c);

#endif
