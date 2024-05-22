/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:26:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/22 11:55:21 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H


# include <dirent.h>
# include "minishell.h"

int		ft_cd(t_ast_n *cmd);
t_mlst	*expand_asterisk(t_ast_n *cmd);

#endif