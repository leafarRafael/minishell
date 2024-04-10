/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:48:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/09 09:54:21 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDING_H
# define EXPANDING_H

#include "key_words.h"
#include "array_lst.h"

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
}		t_expand;


int	ft_expander_lst_token(t_lst *lst);

#endif