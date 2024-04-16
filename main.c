/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/16 14:57:39 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_valid(char *array);
int		ft_exit(char	*input);
void	ft_populetree(t_ast *tree, t_mtrx_mtrx *mtrx_mtrx);
void	ft_printtree(t_ast_node *root);

int main()
{
	t_var_minishell v;

	v.looping_shell = 1;
	while (v.looping_shell)
	{
		v.infile = readline("minishell ~:");
		if (!ft_is_valid(v.infile))
		{
			v.temp__environ = __environ;
			v.env = ft_mtrxdup (__environ);
			__environ = v.env;
			v.input_user = ft_init_lst();
			v.list_matrix = ft_mtrx_mtrx_lst();
			ft_add_string_in_list(v.input_user, v.infile);
			ft_scanner_input(v.input_user);
			while (v.input_user->size > 0)
				ft_create_node_matrix_add_back(v.list_matrix, ft_simple_comand(v.input_user));
			ft_define_cmd_operator(v.list_matrix);
			v.ast = ft_init_ast();
			ft_populetree(v.ast, v.list_matrix);
			//ft_print_todos_os_tokens_expandidos(v.list_matrix);
			ft_delete_mtrx_mtrx_lst(v.list_matrix);
			free(v.input_user);
			v.looping_shell = ft_exit(v.infile);
			free(v.infile);
			ft_delete_cmatrix(v.env);
			__environ = v.temp__environ;
		}
	}
}

void	ft_populetree(t_ast *tree, t_mtrx_mtrx *mtrx_mtrx)
{
	t_mnode		*temp;
	int			i;
	int			type;

	i = 1;
	temp = mtrx_mtrx->head;
	type = temp->type;
	while (i <= mtrx_mtrx->size)
	{
		if (type >= 0)
			ft_build_tree(tree, temp, type);
		temp = temp->next;
		type = temp->type;
		i++;
	}
	ft_printtree(tree->root);
	ft_delete_tree(tree);
}

void ft_printtree(t_ast_node *root)
{
	if (root != NULL)
	{
		ft_print_matrix_line(root->m_lst->matrix);
		printf("esqueda do op: ");
		ft_print_matrix_line(root->m_lst->prev->matrix);
		printf("direita do op: ");
		ft_print_matrix_line(root->m_lst->next->matrix);
		printf("\nnovo op\n");



		ft_printtree(root->left);
		ft_printtree(root->right);
	}
}

int	ft_is_valid(char *array)
{
	int	i;
	int size;

	i = 0;
	size = 0;
	if (!array)
		return (-1);
	size = ft_strlen(array);
	if (size == 0)
	{
		free(array);
		return (-1);
	}
	if (size == 1)
	{
		if (ft_words_delemiter(array[0]))
		{
			free(array);
			return (-1);
		}
		write(2, array, size);
		write(2,": command not found\n", 21);
		free(array);
		return (-1);
	}
	while (array[i])
	{
		if (!ft_words_delemiter(array[i]))
			return (0);
		i++;
	}
	free(array);
	return (-1);
}

int	ft_exit(char	*input)
{
	int	i;

	if (!input)
		return (-1);
	i = 0;
	while (ft_words_delemiter(input[i]))
		i++;
	if (ft_strncmp("exit", &input[i], 4) == 0)
		return (0);
	return (-1);
}