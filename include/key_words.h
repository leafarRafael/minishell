/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_words.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:46:51 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 17:19:24 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_WORDS_H
# define KEY_WORDS_H

typedef enum s_type
{
	NO_OPERATOR_TYPE  = 1 << 0,
	SINGLE_QUOTES = 1 << 1,
	DOUBLE_QUOTES = 1 << 2,
	WHITE_SPACE  = 1 << 3,
	DOLLAR_SIGN = 1 << 4,
	REDI_INFILE = 1 << 5,
	REDIRECT = 1 << 6,
	HERE_DOC = 1 << 7,
	APPEND = 1 << 8,
	PIPE = 1 << 9,
	AND = 1 << 10,
	OR = 1 << 11,
	OPEN_PAREN = 1 << 12,
	CLOSE_PAREN = 1 << 13,
	META_LITERAL = 1 << 14
}       t_type;


int	ft_is_or(char current, char next);
int	ft_is_and(char current, char next);
int	is_pipe(char c);

int	is_operator(int type);
int	is_operator_composite(int c_type, int n_type);

int	ft_is_here_doc(char current, char next);
int	ft_is_append(char current, char next);
int	ft_is_infile(char current);
int	ft_is_outfile(char current);

int	is_double_quotes(char current);
int	is_simple_quotes(char current);

int	is_white_space(char current);
int	is_tab_character(char current);

int	is_dollar(char current);

int	is_open_parenthesis(char c);
int	is_close_parenthesis(char c);


#endif
