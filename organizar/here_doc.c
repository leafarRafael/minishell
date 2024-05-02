/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:05:47 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/02 17:15:51 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void here_doc(t_mtrx_lst *mtrix)
{
	
}

static int	open_here_doc()
{
	int	here_doc[2];

	pipe(here_doc);
}