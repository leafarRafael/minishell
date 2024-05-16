/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:32:34 by tforster          #+#    #+#             */
/*   Updated: 2024/05/15 20:09:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TH_PARSER_H
# define TH_PARSER_H

#include "minishell.h"

typedef enum s_sytx_er
{
	NO_ERROR,
	N_CLS_PRNTH,
	N_OPN_PRNTH,
	N_CLS_DQTS,
	N_CLS_SQTS,
	NON_OPRTR_TYPE,
	BAD_OPRTR_SYNTAX,
	SYNTAX_ERROR,
}			t_sytx_er;

typedef struct s_parse	t_parse;
struct s_parse
{
	t_type_character	type;
	int					start;
	int					size;
	int					close;
	t_parse				*next;
	t_parse				*sub;

};

typedef int (*t_parse_func)(char *, t_parse **, int *);

/* PARSE Functions */
/* Utils*/
t_parse	*parse_new(t_type_character type, int start);
t_parse	*parse_last(t_parse *parse);

// void	parse_add_back(t_parse **parse, t_parse *new_node);
t_parse	*parse_add_back(t_parse **parse, t_parse *new_node);

int		parse_len(t_parse *parse);
void	parse_free(t_parse *parse);

/* Types */
int	parse_quote(char *str, t_parse **parse, int *index);
int	parse_oprtr(char *str, t_parse **parse, int *index);
int	parse_rdrct(char *str, t_parse **parse, int *index);
int	parse_text(char *str, t_parse **parse, int *index);

/* Utils */
int	th_is_tab(int ch);
int	th_is_in_set(char ch, char *set);
int	th_is_quote(char *str, int index);
int	th_is_logical_oprtr(char *str, int index);
int	th_is_io_rdrct(char *str, int index);

void	th_print_parenth(char *str, t_parse *parse, int len);

int	th_syntax_error(t_parse *parse, t_sytx_er error);



#endif
