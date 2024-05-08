/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:52:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/08 15:38:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

typedef struct s_var_infile
{
	char		*file;
	t_lst_line	*c;
	t_lst_line	*next;
	int			index;
	int			size;
}			t_redirect;

int	ft_redirect(t_mlst *mtrix);
int	open_in(t_mlst *mtrix, t_lst_line *lst);
int	open_appnd(t_mlst *mtrix, t_lst_line *lst);
int	open_trnc(t_mlst *mtrix, t_lst_line *lst);
int here_doc(t_mlst *mtrix, t_lst_line *lst);


#endif