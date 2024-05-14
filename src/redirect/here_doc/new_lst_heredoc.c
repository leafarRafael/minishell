/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lst_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:20:40 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/14 10:21:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static void	ft_change_name_file(int *hdoc_ctrlname, t_lst *here_doc);

t_lst *ft_initialize_hdoc_lst(int *hdoc_ctrlname)
{
	t_lst	*here_doc;

	here_doc = ft_init_lst();
	ft_add_string_in_list(here_doc, PATH_HERE_DOC);
	ft_change_name_file(hdoc_ctrlname, here_doc);
	return (here_doc);
}

static void	ft_change_name_file(int *hdoc_ctrlname, t_lst *here_doc)
{
	here_doc->last->c += hdoc_ctrlname[UNIT];
	here_doc->last->prev->c += hdoc_ctrlname[TEN];
	here_doc->last->prev->prev->c += hdoc_ctrlname[HUNDRED];
	here_doc->last->prev->prev->prev->c += hdoc_ctrlname[THOUSAND];
	hdoc_ctrlname[UNIT]++;
	if (hdoc_ctrlname[UNIT] > 9)
	{
		hdoc_ctrlname[UNIT] = 0;
		hdoc_ctrlname[TEN]++;
	}
	if (hdoc_ctrlname[TEN] > 9)
	{
		hdoc_ctrlname[TEN] = 0;
		hdoc_ctrlname[HUNDRED]++;
	}
	if (hdoc_ctrlname[HUNDRED] > 9)
	{
		hdoc_ctrlname[HUNDRED] = 0;
		hdoc_ctrlname[THOUSAND]++;
	}
}
