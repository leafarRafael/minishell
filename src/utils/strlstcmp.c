/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlstcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:39:56 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/29 17:45:03 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_strlstcmp(t_lst *lst, char *str, int size)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_cpy_lst_to_array(lst);
	i = ft_memcmp(new, str, ft_strlen(str)+1);
	free(new);
	return (i);
}