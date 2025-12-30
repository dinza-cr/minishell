/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:03:32 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/13 17:46:51 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_group *group, t_exec *exec)
{
	execve(group->cmd[0], group->cmd, exec->envp);
	ft_safe_exit(exec, group->flag_fail);
}

void	child_process(t_group *group, t_exec *exec)
{
	child_signals();
	ft_redir_pipe(group, exec);
	if (group->flag_fail == 0)
	{
		if ((group->redir_out || group->redir_in || group->app_out)
			&& ft_redir(group))
			ft_safe_exit(exec, 1);
		if (exec->main->hd_del)
			ft_heredoc(exec);
		if (group->cmd && *(group->cmd))
			ft_execve(group, exec);
	}
	else
		ft_safe_exit(exec, group->flag_fail);
	ft_safe_exit(exec, group->flag_fail);
}

void	parent_process(t_group *group, t_exec *exec)
{
	if (group->next)
		close(exec->pipefd[1]);
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	if (group->next)
	{
		exec->prev_fd = exec->pipefd[0];
		exec->pipefd[0] = -1;
	}
	else
		exec->prev_fd = -1;
}

void	exec_execve(t_group *group, t_exec *exec)
{
	pid_t	id;

	id = fork();
	if (id == -1)
	{
		perror("fork");
		return ;
	}
	if (id == 0)
		child_process(group, exec);
	else
	{
		exec->cpid[exec->cpid_index++] = id;
		parent_process(group, exec);
	}
}
