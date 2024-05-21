/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_here_doc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:56:17 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 10:57:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*ft_init_ctrl_name(void);

int	ft_valid_syntax_open_here_doc(t_lst *lst)
{
	t_node		*nd;
	int			*hdoc_ctrlname;
	int			i;

	hdoc_ctrlname = ft_init_ctrl_name();
	i = 1;
	nd = lst->head;
	while (nd->next != lst->head)
	{
		if (nd->type == HERE_DOC)
		{
			ft_finished_hdoc(lst, nd, hdoc_ctrlname);
			nd = lst->head;
		}
		nd = nd->next;
	}
	ft_scanner_input(lst);
	free(hdoc_ctrlname);
	return (-1);
}

static int	*ft_init_ctrl_name(void)
{
	int	*hdoc_ctrlname;

	hdoc_ctrlname = malloc(sizeof(int) * 4);
	hdoc_ctrlname[UNIT] = 0;
	hdoc_ctrlname[TEN] = 0;
	hdoc_ctrlname[HUNDRED] = 0;
	hdoc_ctrlname[THOUSAND] = 0;
	return (hdoc_ctrlname);
}