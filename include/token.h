/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:15 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 14:43:06 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "array_lst.h"
# include "key_words.h"
# include "matrix_lst.h"

typedef struct s_token
{
	t_lst	*new_lst;
	t_node	*node;
	t_node	*next;
	char	*new_str;
	t_lst	temp_lst;
	int		i;
	int		type;
}			t_token;

t_mlst	*ft_token_cmd(t_lst *lst);
void	token_command(t_lst *lst, t_mlst *matrix);
void	token_operator(t_lst *lst, t_mlst *matrix);
void	token_parent(t_lst *lst, t_mlst *matrix);
void	token_after_expand(t_mlst *mlst, t_llst *llst);

#endif