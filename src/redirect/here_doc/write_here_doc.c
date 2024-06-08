/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:57:59 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/08 16:24:28 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "expanding.h"

static t_mlst	*ft_read_std(char *eof);
static int		ft_open_create_here_doc(char *file);
static void		ft_open(char *c_file, char *eof, int expand);
static void		valid_expand(t_lst *l_eof, int *expand);

void	ft_write_here_doc(t_lst *l_file, t_lst *l_eof)
{
	char	*c_file;
	char	*c_eof;
	t_lst	*new_lst;
	int		expand;

	expand = 0;
	valid_expand(l_eof, &expand);
	new_lst = ft_duplst(l_file, ft_cpynode, ft_add_node_back);
	while (new_lst->head->c == '<' || new_lst->head->c == ' ')
		ft_remove_node_front(new_lst);
	c_file = ft_cpy_lst_to_array(new_lst);
	c_eof = ft_cpy_lst_to_array(l_eof);
	ft_open(c_file, c_eof, expand);
	free(c_file);
	free(c_eof);
	ft_delete_list(l_eof);
	ft_delete_list(new_lst);
}

static void	ft_open(char *c_file, char *eof, int expand)
{
	int		i;
	int		fd;
	t_mlst	*mlst;
	t_llst	*line;

	fd = ft_open_create_here_doc(c_file);
	mlst = ft_read_std(eof);
	if (expand == 0)
		ft_expand_m_lst_heredoc(mlst);
	i = 1;
	line = mlst->head;
	while (i <= mlst->size)
	{
		ft_putlst_fd(line->lst, 0, fd);
		write(fd, "\n", 1);
		line = line->next;
		i++;
	}
	ft_delete_matrix(mlst);
	close(fd);
}

static t_mlst	*ft_read_std(char *eof)
{
	t_redirect	h_doc;

	h_doc.size = ft_strlen(eof);
	h_doc.new_mtrx = init_mlst();
	while (1)
	{
		write(2, ">> ", 3);
		h_doc.read_line = get_next_line(STDIN_FILENO);
		if (h_doc.read_line[0] != '\n')
		{
			if (!h_doc.read_line)
				return (NULL);
			if (ft_strncmp(h_doc.read_line, eof, h_doc.size -1) == 0)
			{
				free(h_doc.read_line);
				h_doc.read_line = NULL;
				break ;
			}
			h_doc.new_lst = ft_create_lst_add_str(h_doc.read_line);
			if (h_doc.new_lst->last->c == '\n')
				lst_rmv_back(h_doc.new_lst);
			ft_scanner_simple_operator(h_doc.new_lst);
			ft_add_list_back(h_doc.new_mtrx, h_doc.new_lst);
			free(h_doc.read_line);
			h_doc.read_line = NULL;
		}
		else
			free(h_doc.read_line);
	}
	return (h_doc.new_mtrx);
}

static int	ft_open_create_here_doc(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	return (fd);
}

static void	valid_expand(t_lst *l_eof, int *expand)
{
	t_node	*current;
	t_node	*next;
	int		size;
	int		i;

	i = 1;
	current = l_eof->head;
	next = current->next;
	size = l_eof->size;
	while (i <= l_eof->size)
	{
		if (ft_d_quotes(current->c) || ft_s_quotes(current->c))
		{
			ft_remove_specific_node(l_eof, current);
			(*expand)++;
			i--;
		}
		current = next;
		next = next->next;
		i++;
	}
}
