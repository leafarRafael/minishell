/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:53:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/25 18:24:44 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "minishell.h"

int		ft_find_str_inlist2(t_lst *lst, char *str);
char	*get_prefix(t_node *ptr, t_lst *lst);
char	*get_suffix(t_node *ptr, t_lst *lst);
int		ft_valid_content(t_mlst	*mlst, char *str, int (*func) (t_lst *, char *, int ));
void	ft_expand_lst_wildcard(t_lst *lst, t_mlst *dir_content);

void	expand_wildcard(t_mlst *mlst)
{
	t_llst	*nlst;
	t_llst	*next;
	t_mlst	*asteric_expand;
	int		i;

	i = 0;
	nlst = mlst->head;
	next = nlst->next;
	asteric_expand = expand_current_directory();
	while(i < mlst->size)
	{
		if (find_type_return_ptr(nlst->lst, WILDCARD))
		{
			ft_expand_lst_wildcard(nlst->lst, asteric_expand);
			if (asteric_expand->size != 0)
			{
				insert_lnode_between(mlst, nlst, asteric_expand);
				ft_rmv_spcfc_lst_mtrx(mlst, nlst);
				free(asteric_expand);
				i = 0;
				nlst = mlst->head;
				next = nlst->next;
			}
		}
		else
		{
			i++;
			nlst = next;
			next = next->next;
		}
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
			ft_putlst_fd(lnode->lst, 1, 2);
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

void	ft_expand_lst_wildcard(t_lst *lst, t_mlst *dir_content)
{
	t_node	*asterisk;
	t_node	*temp;
	char	*prefix;
	char	*suffix;
	int		i;

	asterisk = find_type_return_ptr(lst, WILDCARD);
	if (!asterisk)
		return ;
	if (lst->size == 1)
	{
		asterisk->type = META_LITERAL;
		return ;
	}
	prefix = NULL;
	suffix = NULL;
	temp = asterisk;
	prefix = get_prefix(asterisk, lst);
	suffix = get_suffix(asterisk, lst);
	if (prefix)
		ft_valid_content(dir_content, prefix, ft_find_head);
	if (suffix)
		ft_valid_content(dir_content, suffix, ft_find_last);
	asterisk->type = META_LITERAL;
}

char	*get_prefix(t_node *ptr, t_lst *lst)
{
	t_node	*temp;
	t_lst	*lst_prefix;
	char	*prefix;

	if (!lst || !ptr)
		return (NULL);
	if (ptr == lst->head)
		return (NULL);
	temp = ptr->prev;
	lst_prefix = ft_init_lst();
	while (1)
	{
		ft_add_node_front(lst_prefix, ft_cpynode(temp));
		temp = temp->prev;
		if (temp == lst->last)
			break ;
		if (temp->type == WILDCARD)
			break ;
		if (temp->type != NO_OP_TYPE)
			break ;
	}
	prefix = ft_cpy_lst_to_array(lst_prefix);
	ft_delete_list(lst_prefix);
	return (prefix);
}

char	*get_suffix(t_node *ptr, t_lst *lst)
{
	t_node	*temp;
	t_lst	*lst_suffix;
	char	*suffix;

	if (!lst || !ptr)
		return (NULL);
	if (ptr == lst->last)
		return (NULL);
	temp = ptr->next;
	lst_suffix = ft_init_lst();
	while (1)
	{
		ft_add_node_back(lst_suffix, ft_cpynode(temp));
		temp = temp->next;
		if (temp == lst->head)
			break ;
		if (temp->type == WILDCARD)
			break ;
		if (temp->type != NO_OP_TYPE)
			break ;
	}
	suffix = ft_cpy_lst_to_array(lst_suffix);
	ft_delete_list(lst_suffix);
	return (suffix);
}

