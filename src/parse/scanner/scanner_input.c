/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:20:14 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 15:58:56 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	ft_scanner_input(t_lst *lst)
{
	if (!lst || lst->size == 0)
		return ;
	ft_scanner_simple_operator(lst);
	ft_scanner_wildcard(lst);
	ft_scanner_composite(lst);
	ft_scanner_quotes(lst);
	ft_scanner_parenthes(lst);
	ft_scanner_priority_type(lst);
}
