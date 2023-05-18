/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:36:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/18 13:18:50 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <term.h>
# include <dirent.h>
# include <errno.h>

typedef struct s_storage
{
	int					flag;
	char				*name;
	char				*content;
	struct s_storage	*next;
}				t_store;

typedef struct s_shell
{
	int		fd[2];
	int		len;
	char	**cmd;
	char	*res;
	char	*input;
	int		exit_flag;
	int		pipe_flag;
	int		out_flag;
	int		q_flag;
	int		file_err;
	int		empty;
	int		here_limiter;
	char	*limiter;
	t_store	*files;
}				t_shell;

typedef struct s_glob
{
	int		here_flag;
	int		exit_status;
	char	**environ;
	char	*kurva;
}				t_glob;

void	dont_do(char **av);
//history
void	keep_history(char *line, int check);
int		new_history(void);
void	new_history_2(char *hist);
void	hiddenfile_history(char **keep);
//cmds
void	do_cmd(t_shell *data);
void	cmd_child(t_shell *data, int *pipe_fd);
void	execute(t_shell *data, char **cmd);
char	*exable(char **cmd);
void	check_builtin(t_shell *data, char **cmd);
//cmd_tools
char	*find_path(char *cmd);
void	bad_cmd(t_shell *data, char *path);
char	*env_shlvl(void);
int		file_checker(char *path);
//signals
void	sig_handler(int arg);
void	ctrlc(int signum);
void	interupt(int signum);
void	child_quit(int signum);
void	here_child_exit(int signum);
//builtins
char	*this_folder_is(int check);
char	*prev_folder(char *path, int safe);
void	set_pwd_noenv(char *newpwd, char *oldpwd);
void	here_child_exit(int signum);
//pwd
char	*this_folder_is(int check);
char	*set_oldpwd(void);
char	*set_pwd(void);
//cd
char	*relative_cd(char *str);
char	*relative_cd2(char *str);
void	cd_command(char **splited);
char	*prev_folder(char *path, int safe);
//env
void	env_cmd(t_shell *data);
void	set_path_env(char **envp, char *av1);
void	set_under_noenv(void);
// exit
void	ft_exit(t_shell *data);
void	quit(t_shell *data, char *str);
void	ft_exit_part2(t_shell *data);
void	exiting(int arg);
void	child_exit(t_shell *data);
//echo
void	echo_cmd(t_shell *data, char **cmd);
int		strintchr(char	*str, int c);
char	**read_folder(char *str);
char	**read_folder_2(struct dirent *entry, char *str, char **folder, int f);
int		back_check(char *str, char *check);
//export
void	export_cmd(char **cmd);
char	*export_get_lower(char **env, char *to_compare);
char	*export_get_seclow(char **env, char *to_compare);
char	*export_get_big(char **env, char *to_compare);
//export 2
int		export_varmod(char *cmd);
int		export_check_args(char *to_compare, char **cmd);
int		export_check_equal(char *cmd);
void	export_print_error(char *str);
void	very_trash(char	*str, int flag, int to_add);
char	**new_export_env(char **cmd);
// unset
void	unset_cmd(char **cmd, int f);
char	**new_unset_env(char **cmd);
int		unset_check_args(char *to_compare, char **cmd);
//parse
void	parse_input(t_shell *data);
void	parse_input_two(t_shell *data);
t_shell	*data_init(t_shell	*data);
void	output(t_shell *data);
// parse 2
int		space(t_shell *data, char *new, int arg);
int		quote(t_shell *data, char *new);
int		pipex(t_shell *data, char *new);
void	pipex_2(t_shell *data, int arg);
void	how_split(t_shell *data, char **wild);
// parse 3
int		env_var(t_shell *data, char *new);
void	check_substr(t_shell *data, char *new, char c);
char	*remove_quotes(char *str, int qte, int arg, t_shell *data);
char	*get_var(t_shell *data, char *str);
// redirect
int		file_in(t_shell *data, char *new);
int		file_out(t_shell *data, char *new);
void	open_it(t_shell *data);
//here_doc
int		here_doc(t_shell *data);
void	here_child(t_shell *data, int *fd);
void	child_loop(t_shell *data, int *fd, char *buffer);
//splitting
char	**add_split(char **split, char *new);
char	**copy_split(char **split, int arg);
char	**remove_split(char **split, char *rem, int arg);
char	**modify_split(char **split, char *mod, int arg, int flag);
char	**merge_split(char **og, char **new);
//tools
int		get_cmd(char *str, int arg);
void	error(char *msg, int arg);
char	*ft_strjoin_mod(char *str1, char *str2, int pos);
char	*char_join(char *str, int c);
int		check_status(char *msg);
//tools 2
int		end_search(int c);
int		syntax_check(char *str);
int		word_count(char **split);
char	*split_n_join(char *str, char **split, int spliter);
int		check_empty_line(char *line);
// storage
void	store_it(t_shell *data, int flag);
void	make_files(t_shell *data);
void	get_content(t_shell *data);
t_store	*list_last(t_store *lst);
// freedom
void	freesplit(char **splited);
void	*freedom(const char *str, ...);
void	free_check(void *freeable);
void	freelist(t_store *list);
void	clear_data(t_shell *data);

extern t_glob	g_glob;

#endif