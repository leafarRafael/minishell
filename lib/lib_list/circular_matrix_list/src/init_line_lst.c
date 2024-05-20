/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:17:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/20 17:49:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

t_llst	*ft_init_line_lst(void)
{
	t_llst	*line_lst;

	line_lst = NULL;
	line_lst = malloc(sizeof(t_llst));
	if (!line_lst)
		return (NULL);
	line_lst->rdrct = -42;
	line_lst->lst = NULL;
	line_lst->next = NULL;
	line_lst->prev = NULL;
	return (line_lst);
}
