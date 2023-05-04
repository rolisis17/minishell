/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:29:24 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/04 13:43:49 by mstiedl          ###   ########.fr       */
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
# include <term.h>

extern char **environ;

typedef struct  s_shell
{
    int     fd[2];
	int		len;
    char    **cmd;
    char    *res;
    char    *here_doc;
	int		cd_flag;
	int		exit_flag;
	int		exit_status;
	char	**minienv;
}               t_shell;

void	make_history(char *line);
int		check_empty_line(char *line);
void	keep_history(char *line, int check);
void	new_history();
void	hiddenfile_history(char **keep);
//cmds
char	*find_path(char *cmd);
void	bad_cmd(char *path, char **cmd);
void    execute(char **cmd);
void	do_cmd(t_shell *data);
void    data_to_pipe(t_shell *data);
void	check_builtin(char **cmd);
//signals
void    sig_handler(void);
void    ctrlc(int signum);
void    quit(char *str);
//builtins
char	*this_folder_is(int	check);
char	*prev_folder(char *path, int safe);
void	set_oldpwd(void);
void	set_pwd(void);
char    *relative_cd(char *str);
char	*relative_cd2(char *str);
void	cd_command(char **splited);
void    env_cmd(char **cmd);
void	ft_exit(char **cmd);
void	exit_status(char *msg, int check);
int		check_status(char *msg);
void	echo_cmd(char **cmd);
void	export_cmd(char **cmd);
void	unset_cmd(char **cmd);
void	set_path_env(void);
//parse
void	parse_input(char *input);
t_shell *data_init(void);
int     file_in(t_shell *data, char *new);
int     file_out(t_shell *data, char *new);
void	here_new(t_shell *data);
// parse 2
int		space_new(t_shell *data, char *new, int arg);
int		quote_new(t_shell *data, char *new);
char	*env_var(char *data, int len, char *beg);
void	pipex(t_shell *data);
void	output(int *fd);
// parse 3
int		env_var_new(t_shell *data, char *new);
void	check_substr_new(t_shell *data, char *new, char c);
char	*remove_quotes(char *str, int qte, int arg);
//splitting
char	**add_split(char **split, char *new, int arg);
char	**copy_split(char **split, int arg);
char	**remove_split(char **split, char *rem, int arg);
void	freesplit(char **splited);
char	*split_n_join(char *str, char **split, int spliter);
//tools
char    **freedom(char **ted, void *ze, void *dom, void *style);
int		get_cmd(char *str, int arg);
char	*find_quote(char *str, int len);
void	error(char *msg, int arg);
char	*ft_strjoin_mod(char *str1, char *str2, int pos);
char	*char_join(char *str, int c);

#endif