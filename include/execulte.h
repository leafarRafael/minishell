/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execulte.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:54:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/17 17:24:35 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTE_H
# define EXECUTE_H

# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "minishell.h"

typedef struct s_execute
{
	char	**path;
	char	**matrix_cmd;
	char	*path_exe;
	char	*comand;
	pid_t	*pid;
	int		pipe[2];
	t_lst_line *temp;

}	t_execute;


#endif