/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:03:52 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/20 18:55:09 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chose_builtin(t_group *group, t_list_env *env, t_exec *exec, int *code)
{
	(void)exec;
	if (ft_strcmp(group->cmd[0], "cd") == 0)
		*code = ft_cd(group, env);
	else if (ft_strcmp(group->cmd[0], "exit") == 0)
		*code = ft_exit(group, code);
	else if (ft_strcmp(group->cmd[0], "export") == 0)
		*code = ft_export(group, env);
	else if (ft_strcmp(group->cmd[0], "unset") == 0)
		*code = ft_unset(group, &env);
	else if (ft_strcmp(group->cmd[0], "echo") == 0)
		*code = ft_echo(group);
	else if (ft_strcmp(group->cmd[0], "env") == 0)
		*code = ft_env(group, env);
	else if (ft_strcmp(group->cmd[0], "pwd") == 0)
		*code = ft_pwd(group);
}

void	builtin_alone(t_group *group, t_exec *exec, t_list_env *env, int *code)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if ((group->redir_in || group->redir_out
			|| group->app_out) && ft_redir(group))
	{
		*code = 1;
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}
	if (exec->main->hd_del)
		ft_heredoc(exec);
	chose_builtin(group, env, exec, code);
	prompt_signals();
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	child_builtin(t_group *group, t_exec *exec, t_list_env *env, int *code)
{
	child_signals();
	ft_redir_pipe(group, exec);
	if (group->flag_fail == 0)
	{
		if ((group->redir_in || group->redir_out || group->app_out)
			&& ft_redir(group))
			ft_safe_exit(exec, 1);
		if (exec->main->hd_del)
			ft_heredoc(exec);
		if (group->cmd && *(group->cmd))
		{
			chose_builtin(group, env, exec, code);
			if (!ft_strcmp(group->cmd[0], "exit"))
				ft_safe_exit(exec, *code);
		}
	}
	else
		ft_safe_exit(exec, *code);
	ft_safe_exit(exec, *code);
}

void	fork_builtin(t_group *group, t_exec *exec, t_list_env *env, int *code)
{
	pid_t	id;

	id = fork();
	if (id == -1)
	{
		perror("fork");
		return ;
	}
	if (id == 0)
		child_builtin(group, exec, env, code);
	else
	{
		exec->cpid[exec->cpid_index++] = id;
		parent_process(group, exec);
	}
}

void	exec_builtin(t_group *group, t_list_env *env, t_exec *exec, int *code)
{
	if (!group->next && group == exec->start)
		builtin_alone(group, exec, env, code);
	else
		fork_builtin(group, exec, env, code);
	if (!ft_strcmp(group->cmd[0], "exit") && exec->group_count == 1)
		ft_safe_exit(exec, *code);
}
