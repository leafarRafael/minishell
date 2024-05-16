/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/16 17:02:48 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_parser.h"
#include "th_syntax.h"

static int	parse_prnth(char *str, t_parse **parse, int *index);
static int append_sub(char *str, t_parse *parse, int *index, t_parse_func func);

t_parse	*th_parse_param(char *str)
{
	t_parse	*parse;
	int		index;
	size_t	len;
	int		status;

	status = 0;
	len = ft_strlen(str);
	// printf("READLINE LEN = [%zu]\n", len);
	// parse = malloc((len + 1) * sizeof(parse));
	parse = NULL;
	index = 0;
	while (str[index])
	{
		// printf("BASE index[%d] [%c]\n", index, str[index]);
		if (th_is_tab(str[index]))
			index++;
		else if (str[index] == ')')
			status = th_syntax_error(parse, N_OPN_PRNTH);
		else if (str[index] == '(')
			status = parse_prnth(str, &parse, &index);
		else if (th_is_quote(str, index))
			status = parse_quote(str, &parse, &index);
		else if (th_is_logical_oprtr(str, index))
			status = parse_oprtr(str, &parse, &index);
		else if (th_is_io_rdrct(str, index))
			status = parse_rdrct(str, &parse, &index);
		else
			status = parse_text(str, &parse, &index);
		if (status > 0)
		{
			parse_free(parse);
			return (NULL);
		}
	}
	printf("\n");
	printf("RESULT\n");
	th_print_parenth(str, parse, 0);
	printf("RESULT\n");
	th_print_parenth(str, parse, 0);
	return (parse);
}

static int	parse_prnth(char *str, t_parse **parse, int *index)
{
	t_parse				*ptr;
	t_parse				*sub;
	t_type_character	type;
	int					status;

	status = 0;
	ptr = parse_add_back(parse, parse_new(OPEN_PAREN, *index + 1));
	// ptr = parse_last(*parse);
	while (str[(*index)++])
	{
		// printf("PARENTH index[%d] [%c]\n", *index, str[*index]);
		sub = NULL;
		if (th_is_tab(str[*index]))
			ptr->size++;
		else if (str[*index] == '(')
		{
			status = parse_prnth(str, &sub, index);
			if (status > 0)
				return (status);
			(*index)--;
			/* CHANGE THE PTR */
			parse_add_back(&ptr->sub, sub);
			ptr->size += 2 + parse_last(sub)->size;
		}
		else if (str[*index] == '\0')
			return (th_syntax_error(*parse, N_CLS_PRNTH));
		else if (str[*index] == ')')
		{
			(*index)++;
			break ;
		}
		else if (th_is_quote(str, *index))
		{
			status  = append_sub(str, ptr, index, parse_quote);
			// status = parse_quote(str, &sub, index);
			// if (status > 0)
			// 	return (status);
			// (*index)--;
			// ptr->size += 2 + parse_last(sub)->size;
			// parse_add_back(&ptr->sub, sub);
		}
		else if (th_is_logical_oprtr(str, *index))
		{
			status  = append_sub(str, ptr, index, parse_oprtr);
			// status = parse_oprtr(str, &sub, index);
			// if (status > 0)
			// 	return (1);
			// (*index)--;
			// ptr->size += parse_last(sub)->size;
			// parse_add_back(&ptr->sub, sub);
		}
		else if (th_is_io_rdrct(str, *index))
		{
			status  = append_sub(str, ptr, index, parse_rdrct);
			// status = parse_rdrct(str, &sub, index);
			// if (status > 0)
			// 	return (1);
			// (*index)--;
			// ptr->size += parse_last(sub)->size;
			// parse_add_back(&ptr->sub, sub);
		}
		else
		{
			status  = append_sub(str, ptr, index, parse_text);
			// status = parse_text(str, &sub, index);
			// if (status > 0)
			// 	return (1);
			// (*index)--;
			// ptr->size += parse_last(sub)->size;
			// parse_add_back(&ptr->sub, sub);
		}
		if (status > 0)
			return (status);
	}
	return (0);
}

static int append_sub(char *str, t_parse *parse, int *index, t_parse_func func)
{
	t_parse	*sub;
	t_parse	*last;
	int		status;

	sub = NULL;
	// status = parse_oprtr(str, &sub, index);
	status = func(str, &sub, index);
	if (status > 0)
		return (status);
	(*index)--;
	last = parse_add_back(&parse->sub, sub);
	/* FIX THIS SIZE */
	// parse->size += 2 + parse_last(sub)->size;
	parse->size += 2 + last->size;
	return (0);
}


/*
()'1'"12"
01234567
|__\///
\
 \

((cmd1"lixo" arg1" arg2)&&(cmdA&&cmdB)||(cmd2|cmd3 arg3))

(cmd1&|||&&&cmd2)

cmd&&&cmd&&|(cmd&||(cmd|||(cmd||&(cmd|&&(cmd&|&(cmd|&|cmd))))))

// syntax error near unexpected token `||'

<<eof cmd "arg" arg"1" "arg"2 || (cmd && (cmd | cmd > file ))

 */
