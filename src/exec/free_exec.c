/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:58:30 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/20 16:01:56 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_exec_fds(t_exec *exec)
{
	if (exec->prev_fd != -1)
	{
		close(exec->prev_fd);
		exec->prev_fd = -1;
	}
	if (exec->pipefd[0] != -1)
	{
		close(exec->pipefd[0]);
		exec->pipefd[0] = -1;
	}
	if (exec->pipefd[1] != -1)
	{
		close(exec->pipefd[1]);
		exec->pipefd[1] = -1;
	}
}

void	free_exec(t_exec *exec)
{
	int	i;

	if (!exec)
		return ;
	i = 0;
	if (exec->cpid)
	{
		free(exec->cpid);
		exec->cpid = NULL;
	}
	if (exec->envp)
	{
		while (exec->envp[i])
		{
			free(exec->envp[i]);
			i++;
		}
		free(exec->envp);
		exec->envp = NULL;
	}
}

void	ft_safe_exit(t_exec *exec, int nb)
{
	close_exec_fds(exec);
	free_envp_list(exec->env);
	exec->main->group = exec->start;
	free_main(exec->main);
	free_exec(exec);
	clear_history();
	exit(nb);
}
