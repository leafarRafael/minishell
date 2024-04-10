/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:20:14 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/09 15:04:09 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	ft_scanner_input(t_lst *lst)
{
	t_scan	v;

	if (!lst || lst->size == 0)
		return ;
	ft_scanner_parenthes(lst);
	ft_scanner_simple_operator(lst);
	ft_scanner_composite(lst);
	ft_scanner_quotes(lst);
	ft_scanner_priority_type(lst);
}
