/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:26:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/29 17:35:18 by rbutzke          ###   ########.fr       */
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
	_EXPORT
}	t_builtin_size;

#endif

