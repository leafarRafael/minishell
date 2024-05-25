/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:53:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/24 18:58:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

t_mlst	*ft_bubble_sort(t_mlst *mlst);
t_llst	*find_less(t_mlst *mlst);
int		add_lexicographic_value(t_mlst *mlst, char limiter);
t_mlst	*read_directory(char *path);
char	*get_prefix(t_lst *lst, int limiter);
char	*get_sufix(t_lst *lst, int limiter);
t_mlst	*expand_current_directory(void);
int		ft_valid_content(t_mlst	*mlst, char *str, int (*func) (t_lst *, char *, int ));
int		ft_find_head(t_lst *lst, char *str, int size);
int		ft_find_last(t_lst *lst, char *str, int size);

void	expand_wildcard(t_mlst *mlst)
{
	t_llst	*nlst;
	t_llst	*next;
	t_node	*node;
	char	*prefix;
	char	*sufix;
	t_mlst	*asteric_expand;
	int		i;

	i = 0;
	nlst = mlst->head;
	next = nlst->next;
	asteric_expand = expand_current_directory();
	while(i < mlst->size)
	{
		node = find_type_return_ptr(nlst->lst, WILDCARD);
		if (node)
		{
			prefix = get_prefix(nlst->lst, WILDCARD);
			if (prefix)
				ft_valid_content(asteric_expand, prefix, ft_find_head);
			sufix = get_sufix(nlst->lst, WILDCARD);
			if (sufix)
				ft_valid_content(asteric_expand, sufix, ft_find_last);
			node->type = NO_OP_TYPE;
			insert_lnode_between(mlst, nlst, asteric_expand);
			ft_rmv_spcfc_lst_mtrx(mlst, nlst);
			free(asteric_expand);
			i = 0;
			nlst = mlst->head;
			next = nlst->next;
		}
		else
		{
			i++;
			nlst = next;
			next = next->next;
		}
		node = NULL;
	}
}

int	ft_valid_content(t_mlst	*mlst, char *str, int (*func) (t_lst *, char *, int ))
{
	t_llst	*lnode;
	t_llst	*lnnext;
	int		i;

	i = 0;
	lnode = mlst->head;
	lnnext = lnode->next;
	while (i < mlst->size)
	{
		if (!func(lnode->lst, str, ft_strlen(str)))
		{
			ft_rmv_spcfc_lst_mtrx(mlst, lnode);
			i--;	
		}
		i++;
		lnode = lnode->next;
		lnnext = lnnext->next;
	}
	if (mlst->size == 0)
		return (1);
	return (0);
}

char	*get_prefix(t_lst *lst, int limiter)
{
	t_node	*node;
	t_lst	*prefix;
	char	*str_prefix;

	if (!lst)
		return (NULL);
	if (lst->head->type == limiter)
		return (NULL);
	prefix = ft_init_lst();
	node = lst->head;
	while (node->next != lst->head)
	{
		if (node->type != limiter)
			ft_add_node_back(prefix, ft_cpynode(node));
		else
			break ;
		node = node->next;
	}
	str_prefix = ft_cpy_lst_to_array(prefix);
	ft_delete_list(prefix);
	return (str_prefix);
}

char	*get_sufix(t_lst *lst, int limiter)
{
	t_node	*node;
	t_lst	*sufix;
	char	*str_sufix;

	if (!lst)
		return (NULL);
	if (lst->last->type == limiter)
		return (NULL);
	sufix = ft_init_lst();
	node = lst->last;
	while (node->prev != lst->last)
	{
		if (node->type != limiter)
			ft_add_node_front(sufix, ft_cpynode(node));
		else
			break ;
		node = node->prev;
	}
	str_sufix = ft_cpy_lst_to_array(sufix);
	ft_delete_list(sufix);
	return (str_sufix);
}

t_mlst	*expand_current_directory(void)
{
	char	*dir_path;
	t_mlst	*directory_contents;

	dir_path = (char *)getdir_list_string(STRING);
	if (!dir_path)
		return (NULL);
	directory_contents = read_directory(dir_path);
	if (!directory_contents)
		return (NULL);
	free(dir_path);
	return (ft_bubble_sort(directory_contents));	
}

t_mlst	*read_directory(char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_mlst			*mlst;
	t_lst			*lst;

	dir = opendir(path);
	if (dir == NULL)
	{
		ft_msg_error(path, strerror(errno));
		return (NULL);
	}
	mlst = init_mlst();
	while (1)
	{
		dirent = readdir(dir);
		if (dirent == NULL)
			break ;
		lst = ft_init_lst();
		ft_add_string_in_list(lst, dirent->d_name);
		ft_scanner_add_literal(lst);
		ft_add_list_back(mlst, lst);
		lst = NULL;
	}
	closedir(dir);
	return (mlst);
}

int	ft_find_last(t_lst *lst, char *str, int size)
{
	t_node	*node;
	int		index;

	index = size-1;
	node = lst->last;
	while (index >= 0)
	{
		if (node->c != str[index])
			break ;
		node = node->prev;
		index--;
	}
	if (index+1 == 0)
		return (1);
	return (0);
}

int	ft_find_head(t_lst *lst, char *str, int size)
{
	t_node	*node;
	int		index;

	index = 0;
	node = lst->head;
	while (index <= size && str[index])
	{
		if (node->c != str[index])
			break ;
		node = node->next;
		index++;
	}
	if (index == size)
		return (1);
	return (0);
}

t_mlst	*ft_bubble_sort(t_mlst *mlst)
{
	t_llst	*node_a;
	t_llst	*new_n;
	t_mlst	*sort;

	add_lexicographic_value(mlst, '\0');
	sort = init_mlst();
	while (mlst->size > 0)
	{
		if (mlst->size == 1)
			break ;
		node_a = find_less(mlst);
		if (node_a == NULL)
			break ;
		new_n = ft_remove_return_mlst_node(mlst, node_a);
		ft_add_mlstnode_back(sort, new_n);
	}
	free(mlst);
	return (sort);
}

int	add_lexicographic_value(t_mlst *mlst, char limiter)
{
	t_node	*node;
	t_llst	*lnode;
	int		i_m;
	int		i_l;

	i_m = 1;
	lnode = mlst->head;
	while (i_m <= mlst->size)
	{
		i_l = 1;
		node = lnode->lst->head;
		while (i_l <= mlst->size)
		{
			lnode->lex_val += node->lex_val;
			i_l++;
			node = node->next;
			if (node->c == limiter)
				break ;
		}
		i_m++;
		lnode = lnode->next;
	}
}

t_llst	*find_less(t_mlst *mlst)
{
	t_llst	*llst;
	t_llst	*less;

	if (mlst->size == 0)
		return (NULL);
	if (mlst->size == 1)
		return (mlst->head);
	llst = mlst->head;
	less = mlst->head;
	while (llst->next != mlst->head)
	{
		if (llst->lex_val <= less->lex_val)
			less = llst;
		llst = llst->next;
	}
	return (less);
}