/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:29:24 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/15 15:28:36 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

// typedef struct  s_tree
// {
//     int     id;
//     char    *data;
//     s_tree  *right;
//     s_tree  *left;
// }               t_tree;

typedef struct  s_shell
{
    int     fd[2];
    char    **cmd;
    char    *start;
}               t_shell;

int		searchforquotes(char *str, int quote, int start);
void	handle_input(char *line);
void	make_history(char *line);
char	*to_trim_quotes(char *str, int quote);
int		check_empty_line(char *line);
void	error(char *msg, int arg);
//cmds
char	*find_path(char *cmd);
void    execute(char **cmd);
void	bad_cmd(char *path, char **cmd);
//signals
void    sig_handler(void);
void    ctrlc(int signum);
void    quit(char *str);
//builtins
char	*this_folder_is(int	check);
char	*prev_folder(char *path);
void	cd_command(char *str);
void    env_cmd(void);
// parse 2
void	parse_input(char *input);
void    space(t_shell *data, char *new_start);
void	do_cmd(char **cmd, int *fd);
void	output(int *fd);
void	pipex(t_shell *data, char *new_start);
void	envar(void);
int     file_in(t_shell *data, char *new_start);
int     file_out(t_shell *data, char *new_start);
//splitting
char    **add_split(char **split, char *new);
void	freesplit(char **splited);
//tools
char    **freedom(char **split, char *ze, char *dom);
#endif