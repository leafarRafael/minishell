/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getdir_list_or_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:38:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/23 17:54:00 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*getdir_list_string(int str_lst)
{
	t_lst	*lstdir;
	char	*strdir;
	char	buf[300];

	strdir = getcwd(buf, 300);
	if (!strdir)
	{
		perror("..");
		return (NULL);
	}
	if (str_lst == STRING)
		return (ft_strdup(strdir));
	lstdir = ft_init_lst();
	if (ft_add_string_in_list(lstdir, strdir))
		return (NULL);
	free(strdir);
	return (lstdir);
}
