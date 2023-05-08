/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:29:24 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/08 09:27:46 by mstiedl          ###   ########.fr       */
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

typedef struct	s_storage
{
	int					flag;
	char				*name;
	char				*content;
	struct s_storage	*next;
}				t_store;

typedef struct  s_shell
{
    int     fd[2];
	int		len;
    char    **cmd;
    char    *res;
    char    *here_doc;
	int		cd_flag;
	int		exit_flag;
	int		pipe_flag;
	int		out_flag;
	int		exit_status;
	char	**environ;
	char	*kurva;
	t_store	*files;
}               t_shell;

typedef struct	s_glob
{
	int		here_flag;
	int		here_exit;
	int		exit_status;
	char	**environ;
	char	*kurva;
}				t_glob;


char	*check_getenv(char	*str);
void	make_history(char *line);
int		check_empty_line(char *line);
void	keep_history(char *line, int check);
int		new_history();
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
void	interupt(int signum);
void 	here_child_exit(int signum);
//builtins
char	*this_folder_is(int	check);
char	*prev_folder(char *path, int safe);
void	set_oldpwd(void);
void	set_pwd(void);
char    *relative_cd(char *str);
char	*relative_cd2(char *str);
void	cd_command(char **splited);
void    env_cmd(char **cmd);
void	ft_exit(t_shell *data, char *input, char *line);
void	exit_status(char *msg, int check);
int		check_status(char *msg);
void	echo_cmd(char **cmd);
void	export_cmd(char **cmd);
void	export_cmd2(char **cmd, char **cmp, char **args);
int		export_varmod(char *cmd);
char	*export_get_lower(char **env, char *to_compare);
char	*export_get_seclow(char **env, char *to_compare);
char	*export_get_big(char **env, char *to_compare);
int		export_check_equal(char *cmd);
void	export_print_error(char *str);
int		export_check_args(int f, char **cmd);
void	very_trash(char	*str, int flag, int to_add);
void	unset_cmd(char **cmd);
void	set_path_env(char **envp);
char	*env_shlvl(void);
//parse
void	parse_input(char *input);
t_shell *data_init(void);
int     file_in(t_shell *data, char *new);
int     file_out(t_shell *data, char *new);
int		here_doc(t_shell *data);
void	here_child(t_shell *data, int *fd);
// parse 2
int		space_new(t_shell *data, char *new, int arg);
int		quote_new(t_shell *data, char *new);
char	*env_var(char *data, int len, char *beg);
int		pipex(t_shell *data, char *new);
void	output(t_shell *data);
// parse 3
int		env_var_new(t_shell *data, char *new);
void	check_substr_new(t_shell *data, char *new, char c);
char	*remove_quotes(char *str, int qte, int arg);
//splitting
char	**add_split(char **split, char *new, int arg);
char	**copy_split(char **split, int arg);
char	**remove_split(char **split, char *rem, int arg);
char	**modify_split(char **split, char *mod, int arg, int flag);
char	*split_n_join(char *str, char **split, int spliter);
//tools
int		get_cmd(char *str, int arg);
char	*find_quote(char *str, int len);
void	error(char *msg, int arg);
char	*ft_strjoin_mod(char *str1, char *str2, int pos);
char	*char_join(char *str, int c);
int		strintchr(char	*str, int c);
// storage
void	store_it(t_shell *data, int flag);
void	make_files(t_shell *data);
void	get_content(t_shell *data);
t_store	*list_last(t_store *lst);
// freedom
void	freesplit(char **splited);
void    *freedom(const char *str, ...);
void	free_check(void *freeable);
void	freelist(t_store *list);

extern t_glob	g_glob;

#endif