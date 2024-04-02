/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:41:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/02 13:43:03 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "matrix_lst.h"

typedef struct s_variables_parse
{
	t_lst_line	*t_line;
	t_lst		temp_lst;
	t_lst		*lst_current;
	t_node		*node;
	t_node		*current_node;
	t_node		*next_node;
	char		*expand;
	int			found;
	int			index_lst;
	int			index_matrix;

}			t_variables_parse;

int			ft_expander_variable(t_matrix_lst *m_lst);


t_node		*ask_to_expansion(t_matrix_lst *m_lst);
t_node		*ask_expansion(t_matrix_lst *m_lst);
char		*ft_expand(t_node *node, t_node *l_node);

#endif