/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:42:32 by tforster          #+#    #+#             */
/*   Updated: 2024/06/09 15:49:03 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TH_SYNTAX_H
# define TH_SYNTAX_H

# include "th_parser.h"

typedef struct s_stx	t_stx;
struct					s_stx
{
	int	i;
	int	size;
	int	status;
	int	error;
	int	here_doc;
};

int						th_parse_param(char *str);

#endif
