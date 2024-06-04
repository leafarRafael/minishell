/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlstcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:39:56 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 17:37:09 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlstcmp(t_lst *lst, char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_cpy_lst_to_array(lst);
	i = ft_memcmp(new, str, ft_strlen(str) + 1);
	free(new);
	return (i);
}
