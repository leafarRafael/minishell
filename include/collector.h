/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:59:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 10:24:13 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include "abstract_syntax_tree.h"
union mytype
{
	pid_t	pid;
	t_ast	*ast;
};

typedef struct s_n_collector_pid
{
	union mytype				type;
	int							status;
	struct s_n_collector_pid	*next;
	struct s_n_collector_pid	*prev;
}		t_ncollec;


typedef struct s_collector
{
	t_ncollec	*head;
	t_ncollec	*last;
	int			size;
}			t_collector;

t_collector *ft_init_collector(void);
void		*node_collect_pid(void *content);
void		*node_collect_ast(void *content);
int			collector_add_back(t_collector *collec, void *cont, void* (ft_func)(void *));

int			collector_rmv_front(t_collector *collec);
//int			ft_delete_collector(t_collector *collec);

int	ft_delete_collector(t_collector *collec, void (del_content)(t_ast *));

#endif