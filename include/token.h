/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:15 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/10 14:43:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "array_lst.h"
#include "matrix_lst.h"
#include "key_words.h"

typedef struct s_token
{
	t_lst	*new_lst;
	t_node	*node;
	t_node	*next;
	char	*new_str;
	t_lst	temp_lst;
	int		i;
	int		type;
}		t_token;

t_mtrx_lst	*ft_simple_comand(t_lst	*lst);

#endif