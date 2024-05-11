/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_before_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:05:47 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/10 16:10:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "expanding.h"

static t_mlst	*ft_read_std(t_lst *lst, char *eof);

int	here_doc(t_lst *lst)
{
	t_node	*node;
	t_node	*temp;
	t_node	*here_doc;
	t_lst	*lst;
	int		i;

	i = 1;
	node = lst->head;
	lst = ft_init_lst();
	while (i <= lst->size)
	{
		if (node->type == HERE_DOC)
		{
			temp = node;
			break ;
		}
		node = node->next;
		i++;
	}
	lst->head = node;
	temp = temp->next;
	while (temp->type)
	lst->last = node->next;
	return (0);
}

static void dup_here_doc(int fd)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 error");
		return (-1);
	}
	close(fd);
	return (0);
}

/* static void is_op(int op)
{
	return (op & (PIPE | O))
} */