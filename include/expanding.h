/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:48:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 13:32:57 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDING_H
# define EXPANDING_H

# include "array_lst.h"
# include "key_words.h"
# include "matrix_lst.h"

typedef struct s_expandig
{
	t_node	*node;
	t_node	*next_node;
	t_node	*prev_head;
	t_node	*next_last;
	t_lst	lst_temp;
	t_lst	*poin_lst;
	char	*array_var;
	char	*env;
	int		find;
	int		is_head;
	int		is_last;
	int		i;
}			t_expand;

int			ft_expander_lst_token(t_lst *lst);
void		ft_expand_m_lst(t_mlst *lst_matrix);
void		ft_expand_m_lst_heredoc(t_mlst *mlst);
t_mlst		*expand_current_directory(void);
void		expand_wildcard_mlst(t_mlst *mlst);
void		ft_expand_lst_wildcard(t_lst *lst, t_mlst *dir_content);
int			find_prefix(t_lst *inlst, t_lst *this_lst);
int			find_sufix(t_lst *inlst, t_lst *this_lst);
int			find_infix(t_lst *inlst, t_lst *this_lst);

#endif