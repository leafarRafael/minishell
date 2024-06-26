/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:23:10 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 09:23:21 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static int	valid(t_mlst *mtrix, t_llst *line);

int	ft_redirect_manager(t_mlst *mtrix)
{
	t_redirect	v;

	v.index = 1;
	v.c = mtrix->head;
	v.next = v.c->next;
	v.size = mtrix->size;
	if (mtrix->size == 1)
		return (valid(mtrix, v.c));
	while (v.index <= v.size)
	{
		if (valid(mtrix, v.c) < 0)
			return (-1);
		v.index++;
		v.c = v.next;
		if (v.next == v.next->next)
		{
			valid(mtrix, v.next);
			break ;
		}
		v.next = v.next->next;
	}
	return (0);
}

static int	valid(t_mlst *mtrix, t_llst *line)
{
	if (line->rdrct == APPEND)
	{
		if (open_appnd(mtrix, line) < 0)
			return (-1);
	}
	else if (line->rdrct == HERE_DOC)
	{
		if (open_here_doc(mtrix, line) < 0)
			return (-1);
	}
	else if (line->rdrct == REDI_IN)
	{
		if (open_in(mtrix, line) < 0)
			return (-1);
	}
	else if (line->rdrct == REDI_OUT)
	{
		if (open_trnc(mtrix, line) < 0)
			return (-1);
	}
	return (0);
}
