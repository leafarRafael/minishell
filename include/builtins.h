/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:26:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/28 12:33:30 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include <dirent.h>
# include "minishell.h"

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

typedef enum s_builtin_size
{
	_BINARY = 0,
	_CD,
	_PWD,
	_ENV,
	_ECHO,
	_EXIT,
	_UNSET,
	_EXPORT,
	_NULL
}	t_builtin_size;

#endif

