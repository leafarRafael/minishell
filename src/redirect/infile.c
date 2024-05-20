/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:08:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/20 17:49:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

int	open_in(t_mlst *mtrix, t_llst *lst)
{
	char	*infile;
	int		valid_open;

	valid_open = 0;
	infile = ft_cpy_lst_to_array(lst->lst);
	valid_open = ft_myopen(infile, O_RDONLY, 0, STDIN_FILENO);;
	ft_rmv_spcfc_lst_mtrx(mtrix, lst);
	free(infile);
	lst = NULL;
	return (valid_open);
}
