/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_std_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:48:51 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/13 13:46:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "expanding.h"
#include "sigaction.h"

static int	new_str(char *read, char *eof, int size, t_mlst *mlst);
static int	valid(char *read, char *eof, int size, t_mlst *mlst);
static void	new_line(char *read, t_mlst *mlst);

t_mlst	*ft_read_std(char *eof)
{
	t_redirect	h_doc;
	char		*eoff;

	here_signal();
	h_doc.size = ft_strlen(eof);
	h_doc.new_mtrx = init_mlst();
	eoff = ft_strjoin(eof, "\n");
	while (1)
	{
		write(2, ">> ", 3);
		h_doc.read_line = get_next_line(STDIN_FILENO);
		if (valid(h_doc.read_line, eoff, h_doc.size, h_doc.new_mtrx))
			break ;
	}
	free(eoff);
	return (h_doc.new_mtrx);
}

static int	valid(char *read, char *eof, int size, t_mlst *mlst)
{
	if (read)
	{
		if (read[0] != '\n')
		{
			if (new_str(read, eof, size, mlst))
				return (1);
		}
		else
			new_line(read, mlst);
	}
	else
	{
		if (g_status_child != 99)
		{
			ft_putstr_fd(EOF_MSG1, 2);
			ft_putstr_fd(EOF_MSG2, 2);
		}
		return (1);
	}
	return (0);
}

static int	new_str(char *read, char *eof, int size, t_mlst *mlst)
{
	t_lst	*new_lst;

	if (ft_strncmp(read, eof, size +1) == 0)
	{
		free(read);
		read = NULL;
		return (1);
	}
	new_lst = ft_create_lst_add_str(read);
	if (new_lst->last->c == '\n')
		lst_rmv_back(new_lst);
	ft_scanner_simple_operator(new_lst);
	ft_add_list_back(mlst, new_lst);
	free(read);
	read = NULL;
	return (0);
}

static void	new_line(char *read, t_mlst *mlst)
{
	t_lst	*newlst;

	newlst = ft_create_lst_add_str("\r");
	ft_scanner_simple_operator(newlst);
	ft_add_list_back(mlst, newlst);
	free(read);
	read = NULL;
}
