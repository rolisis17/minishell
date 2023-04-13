/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:29:24 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/13 18:52:21 by mstiedl          ###   ########.fr       */
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

typedef struct  s_tree
{
    int     id;
    char    *data;
    s_tree  *right;
    s_tree  *left;
}               t_tree;

int		searchforquotes(char *str, int quote, int start);
void	handle_input(char *line);
void	freesplit(char **splited);
void	make_history(char *line);
char	*to_trim_quotes(char *str, int quote);
int		check_empty_line(char *line);
void	error_func2(char *msg);
//cmds
char	*find_path(char *cmd);
void    execute(char *path, char **cmd);
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

#endif