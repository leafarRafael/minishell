/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:59:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 14:39:27 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H
# include "abstract_syntax_tree.h"
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

union	u_mytype
{
	pid_t	pid;
	t_ast	*ast;
};

typedef struct s_n_collec
{
	union u_mytype		type;
	int					status;
	struct s_n_collec	*next;
	struct s_n_collec	*prev;
}						t_ncllc;

typedef struct s_collector
{
	t_ncllc	*head;
	t_ncllc	*last;
	int		size;
}			t_clct;

t_clct	*ft_init_collector(void);
void	*node_collect_pid(void *content);
void	*node_collect_ast(void *content);
int		cllctr_rmv_front(t_clct *collec);
int		cllctr_add_back( t_clct *collec, void *cont, void *(ft_func)(void *));
int		del_cllctr(t_clct *collec, void (del_content)(t_ast *));

#endif