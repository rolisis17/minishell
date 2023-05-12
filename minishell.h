/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:36:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/12 19:48:25 by dcella-d         ###   ########.fr       */
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
# include <dirent.h>

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
	int		exit_flag;
	int		pipe_flag;
	int		out_flag;
	int		op;
	int		op_char;
	char	*op_data;
	int		op_flag;
	int		new_line; // if 0 nothing in current line has been executed ?
	t_store	*files;
}				t_shell;

typedef struct s_glob
{
	int		here_flag;
	int		exit_status;
	char	**environ;
	char	*kurva;
}				t_glob;

void	keep_history(char *line, int check);
int		new_history(void);
void	hiddenfile_history(char **keep);
int		check_empty_line(char *line);
//cmds
char	*find_path(char *cmd);
void	bad_cmd(char *path, char **cmd);
void	execute(char **cmd);
char	*env_shlvl(void);
void	do_cmd(t_shell *data);
void	check_builtin(char **cmd);
//signals
void	sig_handler(void);
void	ctrlc(int signum);
void	interupt(int signum);
void 	here_child_exit(int signum);
//builtins
char	*this_folder_is(int	check);
char	*prev_folder(char *path, int safe);
void	set_pwd_noenv(char *newpwd, char *oldpwd);
void	here_child_exit(int signum);
void	quit(char *str);
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
void	env_cmd(char **cmd);
void	set_path_env(char **envp);
// exit
void	ft_exit(t_shell *data, char *input);
//echo
void	echo_cmd(char **cmd);
int		strintchr(char	*str, int c);
//export
void	export_cmd(char **cmd);
char	*export_get_lower(char **env, char *to_compare);
char	*export_get_seclow(char **env, char *to_compare);
char	*export_get_big(char **env, char *to_compare);
//export 2
int		export_varmod(char *cmd);
int		export_check_args(int f, char **cmd);
int		export_check_equal(char *cmd);
void	export_print_error(char *str);
void	very_trash(char	*str, int flag, int to_add);
// unset
void	unset_cmd(char **cmd);
//parse
void	parse_input(char *input);
void	parse_input_two(t_shell *data, char *input);
t_shell	*data_init(void);
void	output(t_shell *data);
// parse 2
int		space(t_shell *data, char *new, int arg);
int		quote(t_shell *data, char *new);
int		pipex(t_shell *data, char *new);
int		pipex_new(t_shell *data, char *new);
void	pipex_2(t_shell *data, int arg);
// parse 3
int		env_var(t_shell *data, char *new);
void	check_substr(t_shell *data, char *new, char c);
char	*remove_quotes(char *str, int qte, int arg);
char	*get_var(t_shell *data, char *str);
// redirect
int		file_in(t_shell *data, char *new);
int		file_out(t_shell *data, char *new);
void	open_it(t_shell *data);
//here_doc
int		here_doc(t_shell *data);
void	here_child(t_shell *data, int *fd);
void	child_loop(t_shell *data, int *fd, char *limiter, char *buffer);
//splitting
char	**add_split(char **split, char *new, int arg);
char	**copy_split(char **split, int arg);
char	**remove_split(char **split, char *rem, int arg);
char	**modify_split(char **split, char *mod, int arg, int flag);
char	**merge_split(char **split, char **to_merge, int arg, int flag);
char	*split_n_join(char *str, char **split, int spliter);
int		word_count(char **split);
//tools
int		get_cmd(char *str, int arg);
void	error(char *msg, int arg);
char	*ft_strjoin_mod(char *str1, char *str2, int pos);
char	*char_join(char *str, int c);
int		check_status(char *msg);
//tools 2
int		end_search(int c);
int		back_check(char *str, char *check);
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
//bonus
int		bonus(t_shell *data, char *new);
int		priority(t_shell *data, char *new);
void	get_op_data(t_shell *data);
void	execution(t_shell *data, char *new);
void	clear_pipe(t_shell *data);
int		op_check(t_shell *data);
void	data_to_pipe(t_shell *data);
void	get_op_data(t_shell *data);
char	**wild_cards(char **cmd);

extern t_glob	g_glob;

#endif