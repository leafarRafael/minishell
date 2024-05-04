/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:52:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/04 16:59:58 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

typedef struct s_var_infile
{
	char		*file;
	t_lst_line	*node_c;
	t_lst_line	*node_n;
	int			index;
	int			size;
}			t_redirect;

void	ft_redirect(t_mtrx_lst *mtrix);
void	ft_open_here_doc(t_mtrx_lst *mtrix, t_lst_line *lst);
void	ft_open_infile(t_mtrx_lst *mtrix, t_lst_line *lst);
void	ft_open_append(t_mtrx_lst *mtrix, t_lst_line *lst);
void	ft_opens_truncate(t_mtrx_lst *mtrix, t_lst_line *lst);


#endif