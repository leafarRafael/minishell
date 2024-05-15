/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:42:32 by tforster          #+#    #+#             */
/*   Updated: 2024/05/15 16:29:07 by tforster         ###   ########.fr       */
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
	N_CLS_PRNTH,
	N_OPN_PRNTH,
	N_CLS_DQTS,
	N_CLS_SQTS,
	NON_OPRTR_TYPE,
	BAD_OPRTR_SYNTAX,
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


/** Parser **/
t_parse	*th_parse_param(char *str);

/* Types */
int	parse_quote(char *str, t_parse **parse, int *index);
int	parse_oprtr(char *str, t_parse **parse, int *index);
int	parse_rdrct(char *str, t_parse **parse, int *index);
int	parse_text(char *str, t_parse **parse, int *index);


/* Utils */
int	th_is_tab(int ch);
int	th_is_in_set(char ch, char *set);
int	th_is_quote(char *str, int index);
int	th_is_logical_oprtr(char *str, int index);
int	th_is_io_rdrct(char *str, int index);

void	th_print_parenth(char *str, t_parse *parse, int len);

int	th_syntax_error(t_parse *parse, t_sytx_er error);



#endif
