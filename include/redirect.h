/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:52:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/10 16:12:39 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

typedef struct s_redirect
{
	t_mlst		*new_mtrx;
	t_lst		*new_lst;
	t_lst_line	*line_in_mlst;
	t_lst_line	*c;
	t_lst_line	*next;
	char		*file;
	char		*read_line;
	char		*eof;
	int			index;
	int			size;
	int			i;
	int			here_doc[2];
	int			noting_expand;

}			t_redirect;

int	ft_redirect(t_mlst *mtrix);
int	open_in(t_mlst *mtrix, t_lst_line *lst);
int	open_appnd(t_mlst *mtrix, t_lst_line *lst);
int	open_trnc(t_mlst *mtrix, t_lst_line *lst);
int here_doc(t_mlst *mtrix, t_lst_line *lst);

//here_doc
/* int	ft_create_fd_here_doc(t_lst *lst);
t_mlst	*ft_read_std(t_lst *lst, char *eof); */

#endif