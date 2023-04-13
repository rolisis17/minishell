/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:29:24 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/13 14:12:25 by mstiedl          ###   ########.fr       */
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

int		searchforquots(char *str, int quote);
void	handle_input(char *line);
void	freesplit(char **splited);
void	make_history(char *line);
//cmds
char	*find_path(char *cmd);
void    execute(char *path, char **cmd);
void	bad_cmd(char *path, char **cmd);
//signals
void    sig_handler(void);
void    ctrlc(int signum);
void    quit(char *str);

#endif