/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:42:32 by tforster          #+#    #+#             */
/*   Updated: 2024/05/12 19:22:47 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TH_SYNTAX_H
# define TH_SYNTAX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"

// syntax error near unexpected token `||'

typedef enum s_sytx_er
{
	NO_ERROR,
	NO_CLOSSINSG_PARENTH,
	NO_OPENING_PARENTH,
	NO_CLOSSINSG_D_QUOTES,
	NO_CLOSSINSG_S_QUOTES,
	NON_OPERATOR_TYPE,
	BAD_OPERATOR_SYNTAX,
	SYNTAX_ERROR,
}			t_sytx_er;

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;
}			t_args;

typedef struct s_parse	t_parse;
struct s_parse
{
	t_type_character	type;
	int					start;
	int					size;
	int					close;
	t_parse				*next;
	t_parse				*sub;

};

// /* UTILS Functions */
// void	check_nb_args(int argc, char **argv, int min, int max);
// void	check_pipe(t_pipex *pipex);
// void	close_pipe_fd(int pipe[2]);

// /* ARGS and ENVP Functions */
// t_args	init_args(int argc, char **argv, char **envp);
// char	**envp_path(char **envp);
// void	free_envp_path(char **paths);

// /* CHECK FILE Functins*/
// int		check_file_open(t_pipex pipex, char *file, int mode);

// /* CHECK ACCESS Functions */
// int		check_cmd_access(char **cmd, char **paths, int cmb_nb);

/* PARSE Functions */
/* Utils*/
t_parse	*parse_new(t_type_character type, int start);
t_parse	*parse_last(t_parse *parse);
void	parse_add_back(t_parse **parse, t_parse *new_node);
int		parse_len(t_parse *parse);
void	parse_free(t_parse *parse);
/* Parameters */
t_parse	*th_parse_param(char *str);
// /* Arguments */
// char	**parse_args(char *str);
// void	free_args(char **args);

int	ft_is_tab(int ch);
int	ft_is_in_set(char ch, char *set);

void	print_tabs(int len);
void	print_parenth(t_parse *parse, int len);

int		syntax_error(t_parse *parse, char quote);



#endif
