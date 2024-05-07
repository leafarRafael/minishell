/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:52:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 08:29:46 by rbutzke          ###   ########.fr       */
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

void	ft_redirect(t_mlst *mtrix);
void	ft_open_here_doc(t_mlst *mtrix, t_lst_line *lst);
void	ft_open_infile(t_mlst *mtrix, t_lst_line *lst);
void	ft_open_append(t_mlst *mtrix, t_lst_line *lst);
void	ft_opens_truncate(t_mlst *mtrix, t_lst_line *lst);


#endif