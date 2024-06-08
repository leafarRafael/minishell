/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:59:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/08 14:45:30 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_n_collec
{
	pid_t				pid;
	struct s_n_collec	*next;
	struct s_n_collec	*prev;
}		t_ncollec;

typedef struct s_collector
{
	t_ncollec	*head;
	t_ncollec	*last;
	int			size;
}			t_collector;

typedef struct s_void
{
	void	*head;
	void	*last;
	int		size;
}			t_void;

t_collector *ft_init_collector(void);
t_ncollec	*ft_init_ncollec(void);
int			collector_add_back(t_collector *collec, pid_t pid);
int			collector_rmv_front(t_collector *collec);
int			ft_delete_collector(t_collector *collec);
t_void		*ft_initt_void(void);

#endif