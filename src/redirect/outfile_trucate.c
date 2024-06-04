/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_trucate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:36 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 09:21:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

int	open_trnc(t_mlst *mtrix, t_llst *lst)
{
	char	*outfile;
	int		valid_open;

	valid_open = 0;
	outfile = ft_cpy_lst_to_array(lst->lst);
	valid_open = ft_myopen(outfile,
			O_WRONLY | O_CREAT | O_TRUNC, 0000644, STDOUT_FILENO);
	ft_rmv_spcfc_lst_mtrx(mtrix, lst);
	free(outfile);
	return (valid_open);
}
