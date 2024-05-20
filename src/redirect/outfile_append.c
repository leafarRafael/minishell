/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:44 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/20 17:49:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

int	open_appnd(t_mlst *mtrix, t_llst *lst)
{
	char	*outfile;
	int		valid_open;

	valid_open = 0;
	outfile = ft_cpy_lst_to_array(lst->lst);
	valid_open = ft_myopen(outfile, O_WRONLY | O_CREAT | O_APPEND, 0000644, STDOUT_FILENO);
	ft_rmv_spcfc_lst_mtrx(mtrix, lst);
	lst = NULL;
	free(outfile);
	return (valid_open);
}