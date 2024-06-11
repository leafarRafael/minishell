/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:52:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/11 11:01:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

typedef struct s_redirect
{
	t_mlst	*new_mtrx;
	t_lst	*new_lst;
	t_llst	*line_in_mlst;
	t_llst	*c;
	t_llst	*next;
	char	*file;
	char	*read_line;
	char	*eof;
	int		index;
	int		size;
	int		i;
	int		here_doc[2];
	int		noting_expand;

}			t_redirect;

typedef struct s_hdoc
{
	t_lst	*here_doc;
	t_lst	*lst_eof;
	char	*eof;
	t_node	*end_hdoc;
	t_node	*next;
	t_node	*prev;
	int		is_head;
	int		is_last;
}			t_hdoc;

typedef struct s_add_token
{
	int		count_x;
	int		count_i;
	int		size;
	t_mnode	*mnoode_temp;
	t_llst	*lst_temp;
	t_llst	*lst_next;
}			t_add_token;

int			ft_redirect_manager(t_mlst *mtrix);
int			ft_myopen(char *file, int oflag, int prmssn, int stdfd);
int			open_in(t_mlst *mtrix, t_llst *lst);
int			open_appnd(t_mlst *mtrix, t_llst *lst);
int			open_trnc(t_mlst *mtrix, t_llst *lst);
int			open_here_doc(t_mlst *mtrix, t_llst *lst);
void		ft_finished_hdoc(t_lst *lst, t_node *nd, int *hdoc_ctrlname);
t_lst		*ft_initialize_hdoc_lst(int *hdoc_ctrlname);
t_mlst		*ft_read_std(char *eof);
void		ft_write_here_doc(t_lst *l_file, t_lst *l_eof);
t_mlst		*read_directory(char *path);
t_mlst		*expand_current_directory(void);

#endif