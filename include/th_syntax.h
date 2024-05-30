/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:42:32 by tforster          #+#    #+#             */
/*   Updated: 2024/05/30 16:28:22 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TH_SYNTAX_H
# define TH_SYNTAX_H

# include "th_parser.h"

typedef struct s_stx	t_stx;
struct s_stx
{
	int	error;
	int	here_doc;
};

int	th_parse_param(char *str, t_stx *stx);

#endif
