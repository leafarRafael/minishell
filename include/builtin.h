/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:36:51 by tforster          #+#    #+#             */
/*   Updated: 2024/05/20 19:45:07 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef enum s_builtin
{
	CD = 1,
	ENV = 2,
	PWD = 3,
	ECHO = 4,
	EXIT = 5,
	UNSET = 6,
	EXPORT = 7,
}	t_builtin;

#endif
