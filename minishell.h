/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:29:24 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/19 08:39:17 by mstiedl          ###   ########.fr       */
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

typedef struct  s_shell
{
    int     fd[2];
	int		len;
    char    **cmd;
    char    *res;
}               t_shell;

void	make_history(char *line);
//cmds
char	*find_path(char *cmd);
void	bad_cmd(char *path, char **cmd);
void    execute(char **cmd);
void	do_cmd(char **cmd, int *fd);
//signals
void    sig_handler(void);
void    ctrlc(int signum);
void    quit(char *str);
//builtins
char	*this_folder_is(int	check);
char	*prev_folder(char *path);
void	cd_command(char *str);
void    env_cmd(void);
//parse
void	parse_input(char *input);
int     file_in(t_shell *data, char *new);
int     file_out(t_shell *data, char *new);
int		search_another(t_shell *data, char *str, int sp, int c);
int		check_empty_line(char *line);
// parse 2
int		space(t_shell *data, char *new, int arg);
int     quotes(t_shell *data, char *new);
void	check_substr(t_shell *data, char c);
char	*env_var(char *data, int len, char *beg);
void	pipex(t_shell *data);
void	output(int *fd);

//splitting
char    **add_split(char **split, char *new);
void	freesplit(char **splited);
//tools
char    **freedom(char **split, char *ze, char *dom);
int		get_cmd(char *str, int arg);
char	*find_quote(char *str, int len);
void	error(char *msg, int arg);

#endif