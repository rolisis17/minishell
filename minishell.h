/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:29:24 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/12 21:03:46 by dcella-d         ###   ########.fr       */
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

int		searchforquotes(char *str, int quote, int start);
void	handle_input(char *line);
void	freesplit(char **splited);
void	make_history(char *line);
char	*to_trim_quotes(char *str, int quote);
int		check_empty_line(char *line);
void	error_func2(char *msg);
void	cd_command(char *str);
char	*prev_folder(char *path);
char	*this_folder_is(int	check);
//cmds
char	*find_path(char *cmd);
void    execute(char *path, char **cmd);
void	bad_cmd(char *path, char **cmd);

#endif