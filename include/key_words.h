/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_words.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:46:51 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 17:34:51 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_WORDS_H
# define KEY_WORDS_H

#define _SINGLE_QUOTES_ '\''
#define _DOUBLE_QUOTES_ '"'
#define _DOLLAR_SING_ '$'
#define _REDI_INFILE_ '<'
#define _REDIRECT_ '>'
#define _LEFT_PAREN_ '('
#define _RIGHT_PAREN_ ')'
#define _PIPE_LINE_ '|'
#define _WHITE_SPACE_ is_white_space
#define _HERE_DOC_ ft_is_here_doc
#define _APPEND_ ft_is_append
#define _AND_ ft_is_and
#define _OR_ ft_is_or

typedef enum s_type
{
	NO_OPERATOR_TYPE  = 1 << 0,
	SINGLE_QUOTES = 1 << 1,
	DOUBLE_QUOTES = 1 << 2,
	WHITE_SPACE  = 1 << 3,
	DOLLAR_SING = 1 << 4,
	REDI_INFILE = 1 << 5,
	REDIRECT = 1 << 6,
	HERE_DOC = 1 << 7,
	APPEND = 1 << 8,
	PIPE = 1 << 9,
	AND = 1 << 10,
	OR = 1 << 11,
	LEFT_PAREN = 1 << 12,
	RIGHT_PAREN = 1 << 13,
}       t_type;

int	ft_is_here_doc(char current, char next);
int	ft_is_append(char current, char next);
int	ft_is_or(char current, char next);
int	ft_is_and(char current, char next);
int	is_white_space(char c);

#endif