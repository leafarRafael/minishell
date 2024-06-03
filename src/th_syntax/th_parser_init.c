/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:45:48 by tforster          #+#    #+#             */
/*   Updated: 2024/06/03 16:50:13 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"

t_parse	*parse_init(t_type_character type, int start)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->type = type;
	parse->start = start;
	parse->size = 0;
	parse->close = 0;
	parse->next = NULL;
	parse->prev = NULL;
	parse->sub = NULL;
	return (parse);
}

t_parse	*parse_last(t_parse *parse)
{
	t_parse	*last;

	last = parse;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

t_parse	*parse_add_back(t_parse **parse, t_parse *new_node)
{
	t_parse	*last;

	last = parse_last(*parse);
	if (!last)
		*parse = new_node;
	else
	{
		last->next = new_node;
		new_node->prev = last;
	}
	return (new_node);
}

int	parse_len(t_parse *parse)
{
	int	len;

	len = 0;
	while (parse && parse->size)
	{
		len++;
		parse = parse->next;
	}
	return (len);
}

void	parse_free(t_parse *parse)
{
	t_parse	*temp;

	if (!parse)
		return ;
	while (parse)
	{
		temp = parse;
		if (temp->sub)
			parse_free(temp->sub);
		parse = parse->next;
		free(temp);
	}
}
