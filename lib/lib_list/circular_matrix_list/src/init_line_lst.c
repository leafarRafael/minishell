/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:17:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:23:31 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

t_lst_line	*ft_init_line_lst(void)
{
	t_lst_line	*line_lst;

	line_lst = NULL;
	line_lst = malloc(sizeof(t_lst_line));
	if (!line_lst)
		return (NULL);
	line_lst->rdrct = -42;
	line_lst->lst = NULL;
	line_lst->next = NULL;
	line_lst->prev = NULL;
	return (line_lst);
}
